#pragma once

namespace ssfnlogin
{
	namespace utils
	{
		void launchProgram(const char* program_path, char* arg, const char* launch_path = nullptr);

		void killProcessByName(const char* filename);
	}

}