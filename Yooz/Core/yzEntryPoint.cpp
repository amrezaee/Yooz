#include <yzpch.hpp>

#include <Core/yzApplication.hpp>

extern std::unique_ptr<yz::Application> yz::CreateApp();

extern "C" int main(int argc, char** argv)
{
	yz::Logger::Init(argc, argv);

	std::unique_ptr<yz::Application> app = yz::CreateApp();

	app->Run();

	return 0;
}
