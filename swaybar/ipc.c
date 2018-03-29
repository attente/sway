#define _XOPEN_SOURCE 500
#include <string.h>
#include <strings.h>
#include <json-c/json.h>
#include "swaybar/config.h"
#include "swaybar/ipc.h"
#include "ipc-client.h"

char *parse_font(const char *font) {
	char *new_font = NULL;
	if (strncmp("pango:", font, 6) == 0) {
		font += 6;
	}
	new_font = strdup(font);
	return new_font;
}

static void ipc_parse_colors(
		struct swaybar_config *config, json_object *colors) {
	json_object *background, *statusline, *separator;
	json_object *focused_background, *focused_statusline, *focused_separator;
	json_object *focused_workspace_border, *focused_workspace_bg, *focused_workspace_text;
	json_object *inactive_workspace_border, *inactive_workspace_bg, *inactive_workspace_text;
	json_object *active_workspace_border, *active_workspace_bg, *active_workspace_text;
	json_object *urgent_workspace_border, *urgent_workspace_bg, *urgent_workspace_text;
	json_object *binding_mode_border, *binding_mode_bg, *binding_mode_text;
	json_object_object_get_ex(colors, "background", &background);
	json_object_object_get_ex(colors, "statusline", &statusline);
	json_object_object_get_ex(colors, "separator", &separator);
	json_object_object_get_ex(colors, "focused_background", &focused_background);
	json_object_object_get_ex(colors, "focused_statusline", &focused_statusline);
	json_object_object_get_ex(colors, "focused_separator", &focused_separator);
	json_object_object_get_ex(colors, "focused_workspace_border", &focused_workspace_border);
	json_object_object_get_ex(colors, "focused_workspace_bg", &focused_workspace_bg);
	json_object_object_get_ex(colors, "focused_workspace_text", &focused_workspace_text);
	json_object_object_get_ex(colors, "active_workspace_border", &active_workspace_border);
	json_object_object_get_ex(colors, "active_workspace_bg", &active_workspace_bg);
	json_object_object_get_ex(colors, "active_workspace_text", &active_workspace_text);
	json_object_object_get_ex(colors, "inactive_workspace_border", &inactive_workspace_border);
	json_object_object_get_ex(colors, "inactive_workspace_bg", &inactive_workspace_bg);
	json_object_object_get_ex(colors, "inactive_workspace_text", &inactive_workspace_text);
	json_object_object_get_ex(colors, "urgent_workspace_border", &urgent_workspace_border);
	json_object_object_get_ex(colors, "urgent_workspace_bg", &urgent_workspace_bg);
	json_object_object_get_ex(colors, "urgent_workspace_text", &urgent_workspace_text);
	json_object_object_get_ex(colors, "binding_mode_border", &binding_mode_border);
	json_object_object_get_ex(colors, "binding_mode_bg", &binding_mode_bg);
	json_object_object_get_ex(colors, "binding_mode_text", &binding_mode_text);
	if (background) {
		config->colors.background = parse_color(json_object_get_string(background));
	}
	if (statusline) {
		config->colors.statusline = parse_color(json_object_get_string(statusline));
	}
	if (separator) {
		config->colors.separator = parse_color(json_object_get_string(separator));
	}
	if (focused_background) {
		config->colors.focused_background = parse_color(json_object_get_string(focused_background));
	}
	if (focused_statusline) {
		config->colors.focused_statusline = parse_color(json_object_get_string(focused_statusline));
	}
	if (focused_separator) {
		config->colors.focused_separator = parse_color(json_object_get_string(focused_separator));
	}
	if (focused_workspace_border) {
		config->colors.focused_workspace.border = parse_color(json_object_get_string(focused_workspace_border));
	}
	if (focused_workspace_bg) {
		config->colors.focused_workspace.background = parse_color(json_object_get_string(focused_workspace_bg));
	}
	if (focused_workspace_text) {
		config->colors.focused_workspace.text = parse_color(json_object_get_string(focused_workspace_text));
	}
	if (active_workspace_border) {
		config->colors.active_workspace.border = parse_color(json_object_get_string(active_workspace_border));
	}
	if (active_workspace_bg) {
		config->colors.active_workspace.background = parse_color(json_object_get_string(active_workspace_bg));
	}
	if (active_workspace_text) {
		config->colors.active_workspace.text = parse_color(json_object_get_string(active_workspace_text));
	}
	if (inactive_workspace_border) {
		config->colors.inactive_workspace.border = parse_color(json_object_get_string(inactive_workspace_border));
	}
	if (inactive_workspace_bg) {
		config->colors.inactive_workspace.background = parse_color(json_object_get_string(inactive_workspace_bg));
	}
	if (inactive_workspace_text) {
		config->colors.inactive_workspace.text = parse_color(json_object_get_string(inactive_workspace_text));
	}
	if (binding_mode_border) {
		config->colors.binding_mode.border = parse_color(json_object_get_string(binding_mode_border));
	}
	if (binding_mode_bg) {
		config->colors.binding_mode.background = parse_color(json_object_get_string(binding_mode_bg));
	}
	if (binding_mode_text) {
		config->colors.binding_mode.text = parse_color(json_object_get_string(binding_mode_text));
	}
}

static void ipc_parse_config(
		struct swaybar_config *config, const char *payload) {
	json_object *bar_config = json_tokener_parse(payload);
	json_object *markup, *mode, *hidden_bar, *position, *status_command;
	json_object *font, *bar_height, *wrap_scroll, *workspace_buttons, *strip_workspace_numbers;
	json_object *binding_mode_indicator, *verbose, *colors, *sep_symbol, *outputs;
	json_object_object_get_ex(bar_config, "mode", &mode);
	json_object_object_get_ex(bar_config, "hidden_bar", &hidden_bar);
	json_object_object_get_ex(bar_config, "position", &position);
	json_object_object_get_ex(bar_config, "status_command", &status_command);
	json_object_object_get_ex(bar_config, "font", &font);
	json_object_object_get_ex(bar_config, "bar_height", &bar_height);
	json_object_object_get_ex(bar_config, "wrap_scroll", &wrap_scroll);
	json_object_object_get_ex(bar_config, "workspace_buttons", &workspace_buttons);
	json_object_object_get_ex(bar_config, "strip_workspace_numbers", &strip_workspace_numbers);
	json_object_object_get_ex(bar_config, "binding_mode_indicator", &binding_mode_indicator);
	json_object_object_get_ex(bar_config, "verbose", &verbose);
	json_object_object_get_ex(bar_config, "separator_symbol", &sep_symbol);
	json_object_object_get_ex(bar_config, "colors", &colors);
	json_object_object_get_ex(bar_config, "outputs", &outputs);
	json_object_object_get_ex(bar_config, "pango_markup", &markup);
	if (status_command) {
		free(config->status_command);
		config->status_command = strdup(json_object_get_string(status_command));
	}
	if (position) {
		config->position = parse_position(json_object_get_string(position));
	}
	if (font) {
		free(config->font);
		config->font = parse_font(json_object_get_string(font));
	}
	if (sep_symbol) {
		free(config->sep_symbol);
		config->sep_symbol = strdup(json_object_get_string(sep_symbol));
	}
	if (strip_workspace_numbers) {
		config->strip_workspace_numbers = json_object_get_boolean(strip_workspace_numbers);
	}
	if (binding_mode_indicator) {
		config->binding_mode_indicator = json_object_get_boolean(binding_mode_indicator);
	}
	if (wrap_scroll) {
		config->wrap_scroll = json_object_get_boolean(wrap_scroll);
	}
	if (workspace_buttons) {
		config->workspace_buttons = json_object_get_boolean(workspace_buttons);
	}
	if (bar_height) {
		config->height = json_object_get_int(bar_height);
	}
	if (markup) {
		config->pango_markup = json_object_get_boolean(markup);
	}

	struct config_output *output, *tmp;
	wl_list_for_each_safe(output, tmp, &config->outputs, link) {
		wl_list_remove(&output->link);
		free(output->name);
		free(output);
	}
	if (outputs) {
		int length = json_object_array_length(outputs);
		for (int i = 0; i < length; ++i) {
			json_object *output = json_object_array_get_idx(outputs, i);
			const char *name = json_object_get_string(output);
			if (strcmp("*", name) == 0) {
				// TODO: do we need to clear out the list here or something
				break;
			}
			struct config_output *coutput = calloc(
					1, sizeof(struct config_output));
			coutput->name = strdup(name);
			wl_list_insert(&config->outputs, &coutput->link);
		}
	}

	if (colors) {
		ipc_parse_colors(config, colors);
	}

	json_object_put(bar_config);
}

void ipc_get_config(struct swaybar *bar, const char *bar_id) {
	uint32_t len = strlen(bar_id);
	char *res = ipc_single_command(bar->ipc_socketfd,
			IPC_GET_BAR_CONFIG, bar_id, &len);
	ipc_parse_config(bar->config, res);
	free(res);
}

void handle_ipc_event(struct swaybar *bar) {
	struct ipc_response *resp = ipc_recv_response(bar->ipc_event_socketfd);
	free_ipc_response(resp);
}
