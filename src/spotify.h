#pragma once

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

struct AccessTokenRes {
  std::string access_token;
  std::string token_type;
  std::string scope;
  int expires;
  std::string refresh_token;
};

class Spotify {
private:
  httplib::SSLClient api{"api.spotify.com"};
  httplib::SSLClient accounts{"accounts.spotify.com"};
  std::string access_token;
  std::string refresh_token;
  std::string client_id;
  std::string client_secret;

  std::string GetUserAuth();
  AccessTokenRes GetAccessToken(std::string);

public:
  Spotify(const char* config = "config.json");
};
