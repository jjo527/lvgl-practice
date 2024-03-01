#include <Windows.h>

#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

static void set_temp(void* bar, int32_t temp)
{
    lv_bar_set_value(bar, temp, LV_ANIM_ON);
}

int main()
{
    lv_init();

    /*
     * Optional workaround for users who wants UTF-8 console output.
     * If you don't want that behavior can comment them out.
     *
     * Suggested by jinsc123654.
     */
#if LV_TXT_ENC == LV_TXT_ENC_UTF8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int32_t zoom_level = 100;
    bool allow_dpi_override = false;
    bool simulator_mode = true;
    lv_display_t* display = lv_windows_create_display(
        L"LVGL Windows Simulator Display 1",
        800,
        480,
        zoom_level,
        allow_dpi_override,
        simulator_mode);
    if (!display)
    {
        return -1;
    }

    HWND window_handle = lv_windows_get_display_window_handle(display);
    if (!window_handle)
    {
        return -1;
    }

    HICON icon_handle = LoadIconW(
        GetModuleHandleW(NULL),
        MAKEINTRESOURCE(IDI_LVGL_WINDOWS));
    if (icon_handle)
    {
        SendMessageW(
            window_handle,
            WM_SETICON,
            TRUE,
            (LPARAM)icon_handle);
        SendMessageW(
            window_handle,
            WM_SETICON,
            FALSE,
            (LPARAM)icon_handle);
    }

    lv_indev_t* pointer_indev = lv_windows_acquire_pointer_indev(display);
    if (!pointer_indev)
    {
        return -1;
    }

    lv_indev_t* keypad_indev = lv_windows_acquire_keypad_indev(display);
    if (!keypad_indev)
    {
        return -1;
    }

    lv_indev_t* encoder_indev = lv_windows_acquire_encoder_indev(display);
    if (!encoder_indev)
    {
        return -1;
    }

    // ------------------
    // Layout Stuff

    /*Create a container with ROW flex direction*/
    lv_obj_t* cont_row = lv_obj_create(lv_screen_active());
    lv_obj_set_size(cont_row, 800, 480);
    lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

    /*Create a container with COLUMN flex direction*/
    /*lv_obj_t* cont_col = lv_obj_create(lv_screen_active());
    lv_obj_set_size(cont_col, 200, 150);
    lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);*/

    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_GREEN));


    lv_obj_t* bar = lv_bar_create(cont_row);
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(bar, 150, 350);
    lv_obj_center(bar);
    lv_bar_set_range(bar, 0, 100);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);
    lv_obj_set_flex_flow(bar, LV_FLEX_FLOW_ROW);

    // ------

    static lv_style_t style;
    lv_style_init(&style);

    //lv_style_set_radius(&style, 5);
    //lv_style_set_bg_opa(&style, LV_OPA_COVER);
    //lv_style_set_bg_color(&style, lv_palette_lighten(LV_PALETTE_GREY, 2));
    //lv_style_set_border_width(&style, 2);
    //lv_style_set_border_color(&style, lv_color_black());
    //lv_style_set_pad_all(&style, 10);

    lv_style_set_text_color(&style, lv_color_black());
    lv_style_set_text_font(&style, &lv_font_montserrat_48);
    //lv_style_set_text_letter_space(&style, 5);
    //lv_style_set_text_line_space(&style, 20);
    //lv_style_set_text_decor(&style, LV_TEXT_DECOR_UNDERLINE);

    /*Create an object with the new style*/
    lv_obj_t* obj = lv_label_create(cont_row);
    lv_obj_add_style(obj, &style, 0);
    lv_label_set_text(obj, LV_SYMBOL_BLUETOOTH"\n100 Minutes\nRemaining\n2000 PSI\n15 LPM");
    lv_obj_center(obj);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);

    /*Create a container with COLUMN flex direction*/
    lv_obj_t* cont_col = lv_obj_create(cont_row);
    lv_obj_set_size(cont_col, 300, 400);
    //lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

    /*A base style*/
    static lv_style_t style_base;
    lv_style_init(&style_base);
    lv_style_set_bg_color(&style_base, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
    lv_style_set_border_color(&style_base, lv_palette_darken(LV_PALETTE_LIGHT_BLUE, 3));
    lv_style_set_border_width(&style_base, 2);
    lv_style_set_radius(&style_base, 10);
    lv_style_set_shadow_width(&style_base, 10);
    lv_style_set_shadow_offset_y(&style_base, 5);
    lv_style_set_shadow_opa(&style_base, LV_OPA_50);
    lv_style_set_text_color(&style_base, lv_color_white());
    lv_style_set_width(&style_base, 100);
    lv_style_set_height(&style_base, LV_SIZE_CONTENT);
    lv_style_set_text_font(&style_base, &lv_font_montserrat_48);

    /*Create an object with the base style only*/
    lv_obj_t* obj_base = lv_obj_create(cont_col);
    lv_obj_add_style(obj_base, &style_base, 0);
    lv_obj_align(obj_base, LV_ALIGN_LEFT_MID, 20, 0);

    lv_obj_t* label = lv_label_create(obj_base);
    lv_label_set_text(label, "Settings");
    lv_obj_set_size(obj_base, 250, 100);
    lv_obj_set_flex_flow(label, LV_FLEX_FLOW_COLUMN);

    /*Create an object with the base style only*/
    lv_obj_t* obj_base2 = lv_obj_create(cont_col);
    lv_obj_add_style(obj_base2, &style_base, 0);
    lv_obj_align(obj_base2, LV_ALIGN_LEFT_MID, 20, 0);

    lv_obj_t* label2 = lv_label_create(obj_base2);
    lv_label_set_text(label2, "Charting");
    lv_obj_set_size(obj_base2, 250, 100);
    lv_obj_set_flex_flow(label2, LV_FLEX_FLOW_COLUMN);

    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        //Sleep(time_till_next);

        for (int i = 100; i > 0; i--) {
            lv_bar_set_value(bar, i, LV_ANIM_ON);
            lv_label_set_text_fmt(obj," 3-1-2024\n " LV_SYMBOL_BLUETOOTH " " LV_SYMBOL_BATTERY_3 " " LV_SYMBOL_VOLUME_MAX "\n%d Minutes\nRemaining\n\n%d PSI\n15 LPM", i, i * 20);

            Sleep(100);
            time_till_next = lv_timer_handler();

            if (i > 60) {
                lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_GREEN));
            }
            else if (i > 40) {
                lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_AMBER));
            }
            else if (i > 20) {
                lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_ORANGE));
            }
            else {
                lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
            }
        }
    }

    return 0;
}
