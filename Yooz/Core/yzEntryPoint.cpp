#include <Core/yzApplication.hpp>

#include <yzDeps.hpp>
#include <yzSTD.hpp>


extern "C" int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	yz::AppSpecs as {"Yooz Engine", "/"};

	std::unique_ptr<yz::Application> app = xtd::make_unique<yz::Application>(as);

	app->Run();

	return 0;
}
