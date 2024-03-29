#include "../headers/sputify.hpp"

Sputify::Sputify(Database* database): db(database) {}

void Sputify::mapRoutes(Server& server) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new HomeHandler("template/home.html", this->db));
    server.get("/home.png", new ShowImage("static/sputify.png"));
    server.get("/user.jpg", new ShowImage("static/user.jpg"));
    server.get("/quit.png", new ShowImage("static/quit.png"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/signup", new SignupHandler(this->db));
    server.post("/login", new LoginHandler(this->db));
    server.get("/users", new UsersHandler(this->db));
    server.get("/user", new UserDetailHandler(this->db));
    server.get("/logout", new LogoutHandler(this->db));
    server.post("/follow", new FollowHandler(this->db));
    server.post("/unfollow", new UnfollowHandler(this->db));
    server.get("/add-music", new ShowPage("static/add_music.html"));
    server.post("/add-music", new UploadMusicHandler("template/add_music.html", this->db, &server));
    server.get("/music", new MusicDetailHandler(this->db));
    server.get("/my-musics", new ArtistMusicListHandler(this->db));
    server.get("/add-playlist", new ShowPage("static/add_playlist.html"));
    server.post("/add-playlist", new AddPlaylistHandler(this->db));
    server.post("/add-to-playlist", new AddMusicToPlaylistHandlder(this->db));
    server.get("/my-playlists", new UserPlaylistsHandler(this->db));
    server.get("/playlist", new PlaylistDetailHandler(this->db));
    server.post("/delete-music", new DeleteMusicHandler(this->db));
    server.post("/delete-playlist", new DeletePlaylistHandler(this->db));
    server.get("/musics", new MusicListHandler(this->db));
}

void Sputify::run(int argc, char* argv[]) {
    int port = argc > 1 ? std::stoi(argv[1]) : DEFAULT_PORT;
    Server server(port);
    this->mapRoutes(server);
    std::cout << "Server running on port: " << port << std::endl;
    server.run();
}
