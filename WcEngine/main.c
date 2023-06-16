#include "corange.h"

// globals 
renderer* dr = NULL;
static bool running = true;
static SDL_GLContext* load_context = NULL;

// creating the Croange window, camera and fps counter
void Cinit(){

	// creating the window
	graphics_viewport_set_size(1280, 720);
	graphics_viewport_set_title("render window");
	asset_hndl opt_graphics = asset_hndl_new_load(P("graphics.cfg"));
	dr = renderer_new(opt_graphics);
	renderer_set_skydome_enabled(dr, false);

	// adding a default cube
	folder_load(P("./assets/cube"));
	static_object* s_cube = entity_new("cube", static_object);

	// creating the camera
	entity_new("cam",camera);
	entity_get_as("cam",camera)->far_clip *=4;
	renderer_set_camera(dr, entity_get("cam"));

}

// GTK window activation
static void activate(GtkApplication* app, gpointer user_data){

	// create the builder and load the ui file
	GtkBuilder *builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "builder.ui", NULL);

	// loading the window from the data in builder
	GObject *window = gtk_builder_get_object (builder, "window");
	gtk_window_set_application (GTK_WINDOW (window), app);
	gtk_widget_show (GTK_WIDGET (window));

	// unloading the builder after use
	g_object_unref (builder);

}

// GTK main call
static int GTK_Win(int argc, char **argv){

	// setting SLD graphics context and basic info for GTK
	graphics_context_current(load_context);
	GtkApplication *app;
	int status;

	// creating the window and calling the `activate` function
	app = gtk_application_new("tk.wullie.WcEngine", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	// removing the SDL graphics context and returning GTK status
	graphics_context_delete(load_context);
	return status;
}

// Corange rendering objects
void rendering_render(){

	renderer_add(dr, render_object_static(entity_get("cube")));

}


// main functions, loops updates, calls  functions
int main(int argc, char **argv){

	// load default assets, calls new SDL context and GTK window
	corange_init("../assets_core");
	Cinit();
	GTK_Win(argc, argv);

	// loop for updating the engine 
	while(running){

		frame_begin();
		frame_end_at_rate(60);
		rendering_render();
		renderer_render(dr);
		graphics_swap();
		frame_end();
	
	};

	corange_finish();
	return 0;
}
