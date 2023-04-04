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
  std::string redirect_uri = "http://localhost:8888/callback";

  // Create URL
  std::ostringstream url_stream;
  url_stream << "https://accounts.spotify.com/authorize?response_type=code";
  url_stream << "&client_id=" << httplib::detail::encode_query_param(client_id);
  url_stream << "&redirect_uri=" << httplib::detail::encode_query_param(redirect_uri);
  url_stream << "&scope=" << scope;
  std::string url = url_stream.str();
  
  // Display URL and start callback
  std::cout << "Please visit this website to authorize CPPotify: " << url << std::endl;
  callback.listen("localhost", 8888);
  return code;
}

Spotify::Spotify(const char* config){
  std::ifstream config_file("config.json");
  if (!config_file.good()) throw("config.json could not be loaded.");
  rapidjson::IStreamWrapper isw(config_file);

  rapidjson::Document json;
  json.ParseStream(isw);
  client_id = json["client_id"].GetString();
  client_secret = json["client_secret"].GetString();
  
  std::string authCode = GetUserAuth();
} 
