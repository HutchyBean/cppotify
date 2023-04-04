#include "spotify.h"
#include "tui.h"
#include <exception>

int main(int argc, char *argv[]) {
  try {
    TUI t = TUI(new Spotify());
    t.Render();
  } catch (char const* e) {
    std::cout << "ERROR: " << e << std::endl;
  }
  return 0;
}
