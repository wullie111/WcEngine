#include "corange.h"

static bool running = true;
int main(int argc, char *argv[]) {
	//loads default assets
	corange_init("../../assets_core");

	//creating window
	graphics_viewport_set_size(1280, 720);
	graphics_viewport_set_title("renderWindow");
	asset_hndl opt_graphics = asset_hndl_new_load(P("./graphics.cfg"));
	renderer * dr = renderer_new(opt_graphics);

	//creating camera
	entity_new("cam",camera);
	entity_get_as("cam",camera)->far_clip *=4;
	renderer_set_camera(dr, entity_get("cam"));


	//main loop
	while(running)	{

		frame_begin();
		frame_end_at_rate(60);

		renderer_render(dr);
		graphics_swap();

	
	
	};
	corange_finish();
	return 0;
}
