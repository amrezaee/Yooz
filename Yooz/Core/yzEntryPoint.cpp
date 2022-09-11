#include <Core/yzApplication.hpp>

#include <yzDeps.hpp>
#include <yzStds.hpp>


extern "C" int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	std::unique_ptr<yz::Application> app =
	        std::make_unique<yz::Application>("Yooz", 640, 480);
	app->Execute();
	return 0;
}
