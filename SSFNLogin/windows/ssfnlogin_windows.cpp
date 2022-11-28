#include <Windows.h>

#include "../ssfnlogin.h"
#include "../utils.h"

namespace 
{
    template<typename KeyStrType>
    LSTATUS readRegKey(HKEY mkey, const KeyStrType* key, const KeyStrType* subkey, const DWORD& type, KeyStrType* buffer, const DWORD& size) {
        HKEY hKey;

        auto ret = ERROR_SUCCESS;

        ret = RegOpenKeyEx(mkey, key, 0, KEY_READ, &hKey);

        if (ret == ERROR_SUCCESS)
        {
            DWORD t = type;
            DWORD s = size;
            ret = RegQueryValueEx(hKey, subkey, NULL, &t, (LPBYTE)buffer, &s);
        }

        RegCloseKey(hKey);
        return ret;
    }
}

std::filesystem::path ssfnlogin::getSteamExePath()
{
    char str[256];
    std::format("");
    readRegKey(HKEY_CURRENT_USER, "Software\\Valve\\Steam", "SteamExe", REG_SZ, str, 256);
    return std::filesystem::path(str);
}

void ssfnlogin::killsteam()
{
    ssfnlogin::utils::killProcessByName("steam.exe");
}

void ssfnlogin::launchSteam(const std::filesystem::path& steampath, const std::string& account, const std::string& password)
{
    auto arg = std::format("-noreactlogin -login {} {}", account, password);
    ssfnlogin::utils::launchProgram(steampath.string().c_str(), arg.data(), steampath.parent_path().string().c_str());
}

bool ssfnlogin::parseInput(const std::string& input, std::shared_ptr<std::string>& account, std::shared_ptr<std::string>& password, std::shared_ptr<std::string>& ssfn)
{
    auto index1 = input.find("----");
    if (index1 == std::string::npos)
        return false;
    account = std::make_shared<std::string>(input.substr(0, index1));

    auto index2 = input.find("----", index1 + 4);
    if (index2 == std::string::npos)
        return false;
    password = std::make_shared<std::string>(input.substr(index1 + 4, index2 - index1 - 4));

    ssfn = std::make_shared<std::string>(input.substr(index2 + 4, input.size() - index1 - 4));

    return true;
}
