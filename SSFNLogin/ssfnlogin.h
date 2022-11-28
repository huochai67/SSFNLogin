#pragma once

#include <filesystem>

namespace ssfnlogin {
    std::filesystem::path getSteamExePath();

    void killsteam();

    void launchSteam(const std::filesystem::path& steampath, const std::string& account, const std::string& password);

    bool parseInput(const std::string& input, std::shared_ptr<std::string>& account, std::shared_ptr<std::string>& password, std::shared_ptr<std::string>& ssfn);
}