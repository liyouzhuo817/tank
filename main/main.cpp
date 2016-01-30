#include <boost/filesystem.hpp>
#include <core/core.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
using boost::filesystem::path;
using namespace graphic;
using namespace std::chrono_literals;
int WinMain ()
{
    main(0, 0);
}/*
int WinMain(int argc,char *argv[]){
    main(argc,argv);
}*/
int SDL_main(int argc, char *argv[])
{
    core::engine::init(path("config.xml"));
    //a.checker=new bumpchecker::bumpchecker(a.width,a.height);
    core::engine::load_map(1);
    bool flag = true;
    SDL_Event ev;
    while (flag)
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        start = std::chrono::system_clock::now()+30ms;
        while (SDL_PollEvent(&ev))
        {

            switch (ev.type){
            case SDL_QUIT:
                flag = false;
                break;
            case SDL_KEYDOWN:
                core::engine::key[ev.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                core::engine::key[ev.key.keysym.sym] = false;
                break;
            }
        }
        core::engine::run();
        std::this_thread::sleep_until(start);
    }
    Showmanage::clear_Showmanage();
    return 0;
}
