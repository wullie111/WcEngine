#include "corange.h"

static bool running = true;
renderer* dr = NULL;

void init(){

	//creating window
	graphics_viewport_set_size(1280, 720);
	graphics_viewport_set_title("renderWindow");
	asset_hndl opt_graphics = asset_hndl_new_load(P("./graphics.cfg"));
	dr = renderer_new(opt_graphics);

	//default imported assets
	

	//creating camera
	entity_new("cam",camera);
	entity_get_as("cam",camera)->far_clip *=4;
	renderer_set_camera(dr, entity_get("cam"));

	//fps counter
	ui_button* framerate = ui_elem_new("framerate", ui_button);
	ui_button_move(framerate, vec2_new(10,10));
	ui_button_resize(framerate, vec2_new(30,35));
	ui_button_set_label(framerate, "FRAMERATE");
}


void Rupdate(){

	ui_button_set_label(ui_elem_get("framerate"),frame_rate_string());

}
int main(int argc, char *argv[]){

	//loads default assets
	corange_init("../../assets_core");
	init();
	
	//main loop
	while(running){

		frame_begin();
		frame_end_at_rate(60);
		Rupdate();
		ui_update();
		ui_render();
		renderer_render(dr);
		graphics_swap();
		frame_end();

	
	
	};
	corange_finish();
	return 0;
}

