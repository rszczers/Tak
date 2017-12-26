#define _GNU_SOURCE
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "jpk.h"
#include "config.h"

static void waluta_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->DomyslnyKodWaluty = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void nip_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->NIP = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void pelnanazwa_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->PelnaNazwa = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void regon_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->REGON = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void kraj_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->KodKraju = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void wojewodztwo_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->Wojewodztwo = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void powiat_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->Powiat = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void gmina_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->Gmina = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void ulica_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->Ulica = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void nrdomu_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->NrDomu = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void nrlokalu_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->NrLokalu = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void miejscowosc_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->Miejscowosc = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void kodpocztowy_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->KodPocztowy = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}
static void poczta_callback(GtkWidget* widget, gpointer data) {
    TakConfig* config = (TakConfig*) data;
    config->Poczta = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    saveConfig(config);
}

static void create_sell_col_filter(GtkWidget* widget, JPK* jpk) {
    GtkWidget* check_sell;
    JPKColumns* title = jpk->colNames;
    while(strcmp(title->title, "NrKontrahenta") != 0)
         title = title->next;
    while(strcmp(title->title, "LiczbaWierszySprzedazy") != 0) {
        check_sell = gtk_check_button_new_with_label(title->title);
        gtk_box_pack_start(GTK_BOX(widget), check_sell, 0, 0, 0);
        title = title->next;
    }
}

static void create_pur_col_filter(GtkWidget* widget, JPK* jpk) {
    GtkWidget* check_purchase;
    JPKColumns* title = jpk->colNames;
    while(strcmp(title->title, "NrDostawcy") != 0)
         title = title->next;
    while(strcmp(title->title, "LiczbaWierszyZakupow") != 0) {
        check_purchase = gtk_check_button_new_with_label(title->title);
        gtk_box_pack_start(GTK_BOX(widget), check_purchase, 0, 0, 0);
        title = title->next;
    }
}

static GtkWidget* spreadsheet(JPK* data) {
    GtkWidget* table_sell = gtk_table_new(10, 10, FALSE);
    GtkWidget *entry, *button;
    gtk_table_set_homogeneous(GTK_TABLE(table_sell), FALSE);
    char* buffer = (char*)malloc(64);
    for (int i = 0; i < 10; i++) {
        gtk_table_attach_defaults(GTK_TABLE(table_sell),
                gtk_label_new("Tytuł kolumny"),
                i, i+1, 0, 1);
        for (int j = 1; j < 10; j++) {
            if (i == 0) {
                button = gtk_button_new_with_label("Usuń");
                gtk_table_attach_defaults (GTK_TABLE(table_sell),
                        button,
                        i, i+1, j, j+1);
            } else {
                sprintf (buffer, "(%d,%d)", i, j);
                entry = gtk_entry_new ();
                gtk_entry_set_text (GTK_ENTRY(entry), buffer);
                gtk_table_attach_defaults (GTK_TABLE(table_sell),
                        entry,
                        i, i+1, j, j+1);
            }
        }
    }
    return table_sell;
}

static void open_dialog(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Wybierz plik", GTK_WINDOW(widget),
            GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK,
            GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if (resp == GTK_RESPONSE_OK) {
        g_print("%s\n", gtk_file_chooser_get_filename(
                    GTK_FILE_CHOOSER(dialog)));
    } else {
        g_print("Naciśnięto anuluj\n");
    }
    gtk_widget_destroy(dialog);
}

static void save_dialog(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Wybierz plik", GTK_WINDOW(widget),
            GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_SAVE,
            GTK_RESPONSE_ACCEPT, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if (resp == GTK_RESPONSE_OK) {
        g_print("%s\n", gtk_file_chooser_get_filename(
                    GTK_FILE_CHOOSER(dialog)));
    } else {
        g_print("Naciśnięto anuluj\n");
    }
    gtk_widget_destroy(dialog);
}

static void about_dialog(GtkWidget *widget, gpointer data) {}

static GtkWidget* create_menu_bar() {
    GtkWidget* menu_bar = gtk_menu_bar_new();
    GtkWidget* file_menu = gtk_menu_new();
    GtkWidget* help_menu = gtk_menu_new();
    GtkWidget* menu_item;

    menu_item = gtk_menu_item_new_with_label("Rejestr");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    menu_item = gtk_menu_item_new_with_label("Pomoc");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), help_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    menu_item = gtk_menu_item_new_with_label("Importuj csv");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(open_dialog), NULL);

    menu_item = gtk_menu_item_new_with_label("Importuj xls");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(open_dialog), NULL);

    menu_item = gtk_menu_item_new_with_label("Importuj ods");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(open_dialog), NULL);

    menu_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);

    menu_item = gtk_menu_item_new_with_label("Eksportuj csv");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(save_dialog), NULL);

    menu_item = gtk_menu_item_new_with_label("Eksportuj xml");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(save_dialog), NULL);

    menu_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);

    menu_item = gtk_menu_item_new_with_label("Wyjście");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(gtk_main_quit), NULL);

    menu_item = gtk_menu_item_new_with_label("O programie");
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(about_dialog), NULL);
    return menu_bar;
}

static void create_sell_notebook(GtkWidget *notebook, JPK* jpk) {
    GtkWidget* label_tab = gtk_label_new("Sprzedaże");
    GtkWidget* hbox_sell = gtk_hbox_new(0, 0);
    GtkWidget* vbox_spread = gtk_vbox_new(0, 0);
    GtkWidget* vbox_col_sell = gtk_vbox_new(0, 0);
    create_sell_col_filter(vbox_col_sell, jpk);
    GtkWidget* scroll_col_sell = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_col_sell),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(
            GTK_SCROLLED_WINDOW(scroll_col_sell), vbox_col_sell);
    gtk_widget_set_size_request(scroll_col_sell, 180, 480);
    GtkWidget* scroll_sell = gtk_scrolled_window_new (NULL, NULL);
    // Pseudoarkusz
    GtkWidget* table_sell = spreadsheet(NULL);

    gtk_table_set_row_spacings(GTK_TABLE(table_sell), 1);
    gtk_table_set_col_spacings(GTK_TABLE(table_sell), 1);
    GtkWidget *button_add_row = gtk_button_new_with_label("Dodaj wiersz");
    GtkWidget *hbox_space = gtk_hbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(vbox_spread), table_sell, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox_spread), button_add_row, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox_spread), hbox_space, 1, 1, 0);
    gtk_scrolled_window_add_with_viewport(
            GTK_SCROLLED_WINDOW(scroll_sell), vbox_spread);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scroll_sell),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(hbox_sell), scroll_sell, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(hbox_sell), scroll_col_sell, 0, 0, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox_sell, label_tab);
}

static void create_purchase_notebook(GtkWidget *notebook, JPK* jpk) {
    GtkWidget *label_tab = gtk_label_new("Zakupy");
    GtkWidget* label = gtk_label_new("To jest przykladowy tekst 2 ");
    GtkWidget* hbox_purchase = gtk_hbox_new(0, 0);
    GtkWidget* vbox_col_pur = gtk_vbox_new(0, 0);
    GtkWidget* scroll_col_pur = gtk_scrolled_window_new (NULL, NULL);
    create_pur_col_filter(vbox_col_pur, jpk);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_col_pur),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(
            GTK_SCROLLED_WINDOW(scroll_col_pur), vbox_col_pur);
    gtk_widget_set_size_request(scroll_col_pur, 180, 480);
    gtk_box_pack_start(GTK_BOX(hbox_purchase), label, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(hbox_purchase), scroll_col_pur, 0, 0, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox_purchase, label_tab);
}

static void create_profile_notebook(GtkWidget *notebook, TakConfig* config) {
    GtkWidget *hbox_profile = gtk_hbox_new(1, 0);
    GtkWidget* scroll_profile = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *label_tab = gtk_label_new("Firma");
    GtkWidget *label_profile;
    GtkWidget* table_profile = gtk_table_new(10, 2, FALSE);
    gtk_table_set_col_spacings (GTK_TABLE(table_profile), 20);
    GtkWidget *entry;

    label_profile = gtk_label_new("Waluta");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 0, 1);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(waluta_callback), config);
    if (config->DomyslnyKodWaluty == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->DomyslnyKodWaluty);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 0, 1);

    label_profile = gtk_label_new("Urząd skarbowy");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 1, 2);
    entry = gtk_entry_new();
    GList *combo_items = NULL;
    GtkWidget *combo_entry;
    combo_items = g_list_append(combo_items, "Starachowice");
    combo_items = g_list_append(combo_items, "2");
    combo_items = g_list_append(combo_items, "3");
    combo_items = g_list_append(combo_items, "4");
    combo_entry = gtk_combo_new();
    gtk_combo_set_popdown_strings (GTK_COMBO(combo_entry), combo_items);
    gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(combo_entry)->entry), "Starachowice");
    gtk_entry_set_editable (GTK_ENTRY (GTK_COMBO (combo_entry)->entry), FALSE);
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            combo_entry,
            1, 2, 1, 2);

    label_profile = gtk_label_new("NIP firmy");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 2, 3);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(nip_callback), config);
    if (config->NIP == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->NIP);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 2, 3);

    label_profile = gtk_label_new("Pełna nazwa");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 3, 4);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(pelnanazwa_callback), config);
    if (config->PelnaNazwa == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->PelnaNazwa);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 3, 4);

    label_profile = gtk_label_new("REGON");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 4, 5);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(regon_callback), config);
    if (config->REGON == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->REGON);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 4, 5);

    label_profile = gtk_label_new("Kraj");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 5, 6);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(kraj_callback), config);
    if (config->KodKraju == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->KodKraju);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 5, 6);

    label_profile = gtk_label_new("Województwo");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 6, 7);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(wojewodztwo_callback), config);
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 6, 7);
    if (config->Wojewodztwo == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->Wojewodztwo);
    }

    label_profile = gtk_label_new("Powiat");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 7, 8);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(powiat_callback), config);
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 7, 8);
    if (config->Powiat == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->Powiat);
    }

    label_profile = gtk_label_new("Gmina");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 8, 9);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(gmina_callback), config);
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 8, 9);
    if (config->Gmina == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->Gmina);
    }

    label_profile = gtk_label_new("Ulica");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 9, 10);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(ulica_callback), config);
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 9, 10);
    if (config->Ulica == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->Ulica);
    }

    label_profile = gtk_label_new("Numer domu");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 10, 11);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(nrdomu_callback), config);
    if (config->NrDomu == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->NrDomu);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 10, 11);

    label_profile = gtk_label_new("Numer lokalu");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 11, 12);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(nrlokalu_callback), config);
    if (config->NrLokalu == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->NrLokalu);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 11, 12);

    label_profile = gtk_label_new("Miejcowość");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 12, 13);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(miejscowosc_callback), config);
    if (config->Miejscowosc == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->Miejscowosc);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 12, 13);

    label_profile = gtk_label_new("Kod pocztowy");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 13, 14);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(kodpocztowy_callback), config);
    if (config->KodPocztowy == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->KodPocztowy);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 13, 14);

    label_profile = gtk_label_new("Poczta");
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            label_profile,
            0, 1, 14, 15);
    entry = gtk_entry_new();
    g_signal_connect(entry, "changed", G_CALLBACK(poczta_callback), config);
    if (config->Poczta == NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry), config->Poczta);
    }
    gtk_table_attach_defaults(
            GTK_TABLE(table_profile),
            entry,
            1, 2, 14, 15);

    gtk_box_pack_start(GTK_BOX(hbox_profile), table_profile, 0, 0, 0);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_profile),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(
            GTK_SCROLLED_WINDOW(scroll_profile), hbox_profile);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scroll_profile, label_tab);
}

static GtkWidget* create_notebooks(JPK* jpk, TakConfig* config) {
    GtkWidget *notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
    create_sell_notebook(notebook, jpk);
    create_purchase_notebook(notebook, jpk);
    create_profile_notebook(notebook, config);
    return notebook;
}

static GtkWidget* create_box_bottom() {
    GtkWidget* hbox_bottom = gtk_hbox_new(0, 15);
    GtkWidget* radio_aim_gr = gtk_radio_button_new_with_label(NULL,
            "Złożenie po raz pierwszy");
    gtk_box_pack_start(GTK_BOX(hbox_bottom), radio_aim_gr, 0, 1, 0);
    GtkWidget* radio_aim = gtk_radio_button_new_with_label(
         gtk_radio_button_get_group(
          GTK_RADIO_BUTTON(radio_aim_gr)), "Pierwsza korekta");
    gtk_box_pack_start(GTK_BOX(hbox_bottom), radio_aim, 0, 1, 0);
    radio_aim = gtk_radio_button_new_with_label(
         gtk_radio_button_get_group(
          GTK_RADIO_BUTTON(radio_aim_gr)), "Druga korekta");
    gtk_box_pack_start(GTK_BOX(hbox_bottom), radio_aim, 0, 1, 0);
    return hbox_bottom;
}

void drawGui(JPK* jpk) {
    TakConfig* config = parseConfig();
    gtk_init(NULL, NULL);
    GtkWidget *window, *vbox;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete_event", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), create_menu_bar(), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), create_notebooks(jpk, config), 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), create_box_bottom(), 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_set_size_request(window, 800, 600);
    gtk_widget_show_all(window);
    gtk_main();
}

