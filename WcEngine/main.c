#include "corange.h"

// globals 
renderer* dr = NULL;
static bool running = true;
static SDL_GLContext* load_context = NULL;
GMenu *menu;
GtkWidget *window;

// creating the Croange window, camera and fps counter
void Cinit(){

	// creating the window
	graphics_viewport_set_size(1280, 720);
	graphics_viewport_set_title("render window");
	asset_hndl opt_graphics = asset_hndl_new_load(P("./.WcEngine/graphics.cfg"));
	dr = renderer_new(opt_graphics);
	renderer_set_skydome_enabled(dr, false);

	// adding a default cube
	folder_load(P("./assets/cube"));
	static_object* s_cube = entity_new("cube", static_object);

	// creating the camera
	entity_new("cam",camera);
	entity_get_as("cam",camera)->far_clip *=4;
	renderer_set_camera(dr, entity_get("cam"));

	// creating the FPS counter
	ui_button* framerate = ui_elem_new("framerate", ui_button);
	ui_button_move(framerate, vec2_new(10, 10));
	ui_button_resize(framerate, vec2_new(30, 30));
	ui_button_set_label(framerate, "framerate");

}

// GTK window activation
static void activate(GtkApplication* app, gpointer user_data){

	// create the builder and load the ui file
	GtkBuilder *builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "./.WcEngine/builder.ui", NULL);

	// loading the window from the data in builder
	GObject *window = gtk_builder_get_object (builder, "window");
	gtk_window_set_application (GTK_WINDOW (window), app);
	gtk_widget_show (GTK_WIDGET (window));

	// unloading the builder after use
	g_object_unref (builder);

}

// creating a GTK menu to handle system info, e.g the `FILE` option
static gint menuBox(GtkWidget *widget, GdkEvent *event){

	// GTK/GDK pointers
	GtkMenuButton *event_button;

	// checking for failures (not me)
	g_return_val_if_fail(widget != NULL, FALSE);
	g_return_val_if_fail(G_IS_MENU(widget), FALSE);
	g_return_val_if_fail(event != NULL, FALSE);

	// setting up the menu widget so it can be called with g_signal_connect_swapped
	menu = G_MENU (widget);

	if(event->type == GDK_BUTTON_PRESS){
		event_button = (GtkMenuButton *) event;

		if(event_button->button == GDK_BUTTON_SECONDARY){
			gtk_menu_popup (menu, NULL, NULL, NULL, NULL, event_button->button, event_button->time);

			return TRUE;
		}
	
	}
	return FALSE;
}

// GTK main call
static int GTK_Win(int argc, char **argv){

	// setting SLD graphics context and basic info for GTK
	graphics_context_current(load_context);
	GtkApplication *app;
	int status;

	// creating the window and calling the `activate` function
	app = gtk_application_new("org.Wc.WcEngine", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	g_signal_connect_swapped(window, "button_press_event", G_CALLBACK (menuBox), menu);
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
	corange_init("./.WcEngine/assets_core");
	GTK_Win(argc, argv);
	Cinit();

	// loop for updating the engine 
	while(running){

		frame_begin();
		frame_end_at_rate(60);
		rendering_render();
		ui_update();
		ui_render();
		renderer_render(dr);
		graphics_swap();
		frame_end();
	
	};

	corange_finish();
	return 0;
}
