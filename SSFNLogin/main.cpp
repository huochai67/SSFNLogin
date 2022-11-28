#include <iostream>
#include <string_view>
#include <filesystem>

#include <Windows.h>
#include <iostream>

#include "ssfnlogin.h"

void PostErrorAndExit(const char* str) {
    std::cout << str << std::endl;
    exit(0);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        PostErrorAndExit("Usage: ssfnlogin [account----password----ssfn]");
    }

    std::string input = argv[1];
    std::shared_ptr<std::string> account;
    std::shared_ptr<std::string> password;
    std::shared_ptr<std::string> ssfn;
    if (!ssfnlogin::parseInput(input, account, password, ssfn))
    {
        PostErrorAndExit("Usage: ssfnlogin [account----password----ssfn]");
    }

    auto path = ssfnlogin::getSteamExePath();
    auto dir = path.parent_path();

    ssfnlogin::killsteam();

    ssfnlogin::launchSteam(path, *account.get(), *password.get());
    
    return 0;
}