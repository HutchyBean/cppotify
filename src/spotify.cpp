#include "spotify.h"
#include "httplib.h"

#include <filesystem>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

std::string Spotify::GetUserAuth() {
  // Setup webserver
  std::string code;
  httplib::Server callback;
  callback.Get("/callback", [&](const httplib::Request& req, httplib::Response res){
      code = req.get_param_value("code");
      res.set_content("nice", "text/plain");
      callback.stop();
  });

  // Define paramaters
  std::string scope = "user-read-playback-state user-modify-playback-state user-read-currently-playing playlist-read-private playlist-read-collaborative";

  // Create URL
  std::ostringstream url_stream;
  url_stream << "https://accounts.spotify.com/authorize?response_type=code";
  url_stream << "&client_id=" << httplib::detail::encode_query_param(client_id);
  url_stream << "&redirect_uri=" << httplib::detail::encode_query_param("http://localhost:8888/callback");
  url_stream << "&scope=" << httplib::detail::encode_query_param(scope);
  std::string url = url_stream.str();
  
  // Display URL and start callback
  std::cout << "Please visit this website to authorize CPPotify: " << url << std::endl;
  callback.listen("localhost", 8888);
  return code;
}
AccessTokenRes Spotify::GetAccessToken(std::string code) {
  std::ostringstream form;
  form << "grant_type=authorization_code";
  form << "&redirect_uri=" << httplib::detail::encode_query_param("http://localhost:8888/callback");
  form << "&code=" << httplib::detail::encode_query_param(code);

  httplib::Headers headers = {
    {"Authorization", "Basic " + httplib::detail::base64_encode(this->client_id + ":" + this->client_secret)}
  };

  auto res = this->accounts.Post("/api/token", headers, form.str(), "application/x-www-form-urlencoded");
  if (res->status != 200) throw("error getting access token.");

  rapidjson::Document json;
  AccessTokenRes response;

  json.Parse(res->body.c_str());

  response.access_token = json["access_token"].GetString();
  response.scope = json["scope"].GetString();
  response.refresh_token = json["refresh_token"].GetString();
  response.token_type = json["token_type"].GetString();
  response.expires = json["expires_in"].GetInt();

  return response;
}


Spotify::Spotify(const char* config){
  std::ifstream config_file("config.json");
  if (!config_file.good()) throw("config.json could not be loaded.");
  rapidjson::IStreamWrapper isw(config_file);

  rapidjson::Document json;
  json.ParseStream(isw);
  client_id = json["client_id"].GetString();
  client_secret = json["client_secret"].GetString();
  
  std::string auth_code = GetUserAuth();
  AccessTokenRes access_stuff = GetAccessToken(auth_code);
  this->access_token = access_stuff.access_token;
  this->refresh_token = access_stuff.refresh_token;
} 

