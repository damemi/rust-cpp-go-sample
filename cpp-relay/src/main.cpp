#include <httplib.h>

#include <cstdlib>
#include <string>

int main() {
  const char *go_url = std::getenv("GO_SERVICE_URL");
  if (!go_url || !*go_url) {
    go_url = "http://127.0.0.1:8080";
  }

  httplib::Server s;

  s.Get("/invoke", [go_url](const httplib::Request &, httplib::Response &res) {
    httplib::Client cli(go_url);
    cli.set_connection_timeout(5, 0);
    cli.set_read_timeout(10, 0);
    auto upstream = cli.Get("/");
    if (!upstream) {
      res.status = 502;
      res.set_content("failed to reach go service", "text/plain");
      return;
    }
    if (upstream->status != 200) {
      res.status = 502;
      res.set_content("go returned " + std::to_string(upstream->status),
                      "text/plain");
      return;
    }
    res.status = 200;
    res.set_content(std::string("cpp relayed: ") + upstream->body,
                    "text/plain");
  });

  s.Get("/health", [](const httplib::Request &, httplib::Response &res) {
    res.status = 200;
    res.set_content("ok", "text/plain");
  });

  const char *port_env = std::getenv("PORT");
  int port = 8080;
  if (port_env && *port_env) {
    port = std::atoi(port_env);
    if (port <= 0) {
      port = 8080;
    }
  }

  if (!s.listen("0.0.0.0", port)) {
    return 1;
  }
  return 0;
}
