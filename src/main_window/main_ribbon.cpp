#include "main_ribbon.h"

MainRibbon::MainRibbon(QWidget* parent) : QRibbon(parent) {
	// Home
	QRibbonTab* home_tab = new QRibbonTab;

	// Undo/Redo History
	QRibbonSection* history_section = new QRibbonSection;
	history_section->setText("历史");

	undo->setIcon(QIcon("data/icons/ribbon/undo32x32.png"));
	undo->setText("撤销");
	history_section->addWidget(undo);

	redo->setIcon(QIcon("data/icons/ribbon/redo32x32.png"));
	redo->setText("重做");
	history_section->addWidget(redo);

	QRibbonSection* editor_section = new QRibbonSection;
	editor_section->setText("编辑/查看");

	trigger_editor->setIcon(QIcon("Data/Icons/Ribbon/triggereditor32x32.png"));
	trigger_editor->setText("触发器\n编辑器");
	editor_section->addWidget(trigger_editor);

	object_editor->setIcon(QIcon("data/icons/ribbon/objecteditor32x32.png"));
	object_editor->setText("对象\n编辑器");
	editor_section->addWidget(object_editor);

	model_editor->setIcon(QIcon("data/icons/ribbon/model_editor.png"));
	model_editor->setText("模型\n编辑器");
	editor_section->addWidget(model_editor);

	QRibbonSection* palette_section = new QRibbonSection;
	palette_section->setText("调色板");

	terrain_palette->setIcon(QIcon("data/icons/ribbon/heightmap32x32.png"));
	terrain_palette->setText("地形");
	palette_section->addWidget(terrain_palette);

	doodad_palette->setIcon(QIcon("data/icons/ribbon/doodads32x32.png"));
	doodad_palette->setText("装饰物");
	palette_section->addWidget(doodad_palette);

	unit_palette->setIcon(QIcon("data/icons/ribbon/units32x32.png"));
	unit_palette->setText("单位");
	palette_section->addWidget(unit_palette);

	pathing_palette->setIcon(QIcon("data/icons/ribbon/pathing32x32.png"));
	pathing_palette->setText("路径");
	palette_section->addWidget(pathing_palette);



	//view_history->setIcon(QIcon("data/icons/ribbon/description32x32.png"));
	//view_history->setText("View\nHistory");
	//view_history->setEnabled(false);
	//history_section->addWidget(view_history);

	/*copy->setIcon(QIcon("data/icons/ribbon/copy32x32.ico"));
	copy->setText("Copy");
	home_section->addWidget(copy);

	paste->setIcon(QIcon("data/icons/ribbon/paste32x32.ico"));
	paste->setText("Paste");
	home_section->addWidget(paste);

	QVBoxLayout* lay = new QVBoxLayout;
	QToolButton* but = new QToolButton;
	QToolButton* butt = new QToolButton;
	QToolButton* buttt = new QToolButton;

	but->setIcon(QIcon("data/icons/ribbon/paste32x32.ico"));
	but->setIconSize({ 16, 16 });
	but->setText("Cut");
	but->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);*/

	//lay->addWidget(but);
	//lay->addWidget(butt);
	//lay->addWidget(buttt);

	//history_section->addLayout(lay);
	home_tab->addSection(history_section);
	home_tab->addSection(editor_section);
	home_tab->addSection(palette_section);

	// View
	QRibbonTab* view_tab = new QRibbonTab;

	// Visible section
	QRibbonSection* visible_section = new QRibbonSection;
	visible_section->setText("可见");
	view_tab->addSection(visible_section);
	
	units_visible->setIcon(QIcon("data/icons/ribbon/units32x32.png"));
	units_visible->setText("单位");
	units_visible->setCheckable(true);
	units_visible->setChecked(true);
	visible_section->addWidget(units_visible);

	doodads_visible->setIcon(QIcon("data/icons/ribbon/doodads32x32.png"));
	doodads_visible->setText("装饰物");
	doodads_visible->setCheckable(true);
	doodads_visible->setChecked(true);
	visible_section->addWidget(doodads_visible);

	pathing_visible->setIcon(QIcon("data/icons/ribbon/pathing32x32.png"));
	pathing_visible->setText("路径");
	pathing_visible->setCheckable(true);
	visible_section->addWidget(pathing_visible);
	
	brush_visible->setIcon(QIcon("data/icons/ribbon/brush32x32.png"));
	brush_visible->setText("画刷");
	brush_visible->setCheckable(true);
	brush_visible->setChecked(true);
	visible_section->addWidget(brush_visible);

	lighting_visible->setIcon(QIcon("data/icons/ribbon/lighting32x32.png"));
	lighting_visible->setText("光照");
	lighting_visible->setCheckable(true);
	lighting_visible->setChecked(true);
	visible_section->addWidget(lighting_visible);

	water_visible->setIcon(QIcon("data/icons/ribbon/water32x32.png"));
	water_visible->setText("水体");
	water_visible->setCheckable(true);
	water_visible->setChecked(true);
	visible_section->addWidget(water_visible);

	click_helpers_visible->setIcon(QIcon("data/icons/ribbon/click_helpers.png"));
	click_helpers_visible->setText("点击\n辅助");
	click_helpers_visible->setCheckable(true);
	click_helpers_visible->setChecked(true);
	visible_section->addWidget(click_helpers_visible);

	wireframe_visible->setIcon(QIcon("data/icons/ribbon/wireframe32x32.png"));
	wireframe_visible->setText("线框");
	wireframe_visible->setCheckable(true);
	visible_section->addWidget(wireframe_visible);

	debug_visible->setIcon(QIcon("data/icons/ribbon/debug32x32.png"));
	debug_visible->setText("调试");
	debug_visible->setCheckable(true);
	visible_section->addWidget(debug_visible);

	minimap_visible->setIcon(QIcon("data/icons/ribbon/minimap32x32.png"));
	minimap_visible->setText("小地图");
	minimap_visible->setCheckable(true);
	minimap_visible->setChecked(true);
	visible_section->addWidget(minimap_visible);
	// Camera section
	QRibbonSection* camera_section = new QRibbonSection;
	camera_section->setText("镜头");
	view_tab->addSection(camera_section);

	reset_camera->setIcon(QIcon("data/icons/ribbon/reset32x32.png"));
	reset_camera->setText("重置");
	camera_section->addWidget(reset_camera);

	// Menu actions
	new_map->setText("新建地图");
	new_map->setIcon(QIcon("data/icons/ribbon/new32x32.ico"));
	new_map->setIconSize({ 32, 32 });
	new_map->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	new_map->setDisabled(true);
	addMenuItem(new_map);

	open_map_folder->setText("打开地图（文件夹）");
	open_map_folder->setIcon(QIcon("data/icons/ribbon/open32x32.png"));
	open_map_folder->setIconSize({ 32, 32 });
	open_map_folder->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(open_map_folder);

	open_map_mpq->setText("打开地图（MPQ）");
	open_map_mpq->setIcon(QIcon("data/icons/ribbon/open32x32.png"));
	open_map_mpq->setIconSize({ 32, 32 });
	open_map_mpq->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(open_map_mpq);

	save_map->setText("保存地图");
	save_map->setIcon(QIcon("data/icons/ribbon/save32x32.png"));
	save_map->setIconSize({ 32, 32 });
	save_map->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(save_map);

	save_map_as->setText("另存地图");
	save_map_as->setIcon(QIcon("data/icons/ribbon/saveas32x32.png"));
	save_map_as->setIconSize({ 32, 32 });
	save_map_as->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(save_map_as);

	export_mpq->setText("导出MPQ");
	export_mpq->setIcon(QIcon("data/icons/ribbon/saveas32x32.png"));
	export_mpq->setIconSize({ 32, 32 });
	export_mpq->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(export_mpq);

	test_map->setText("测试地图");
	test_map->setIcon(QIcon("data/icons/ribbon/test32x32.ico"));
	test_map->setIconSize({ 32, 32 });
	test_map->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(test_map);

	settings->setText("设置");
	settings->setIcon(QIcon("data/icons/ribbon/options32x32.png"));
	settings->setIconSize({ 32, 32 });
	settings->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(settings);

	addMenuSeperator();

	exit->setText("退出");
	exit->setIcon(QIcon("data/icons/ribbon/exit32x32.ico"));
	exit->setIconSize({ 32, 32 });
	exit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	addMenuItem(exit);

	// Map tab
	QRibbonTab* map_tab = new QRibbonTab;

	QRibbonSection* map_section = new QRibbonSection;

	map_description->setIcon(QIcon("data/icons/ribbon/description32x32.png"));
	map_description->setText("描述");
	map_section->addWidget(map_description);

	map_loading_screen->setIcon(QIcon("data/icons/ribbon/loading32x32.png"));
	map_loading_screen->setText("载入\n界面");
	map_section->addWidget(map_loading_screen);

	map_options->setIcon(QIcon("data/icons/ribbon/options32x32.png"));
	map_options->setText("选项");
	map_section->addWidget(map_options);

	//map_size_camera_bounds->setIcon(QIcon("data/icons/ribbon/sizebounds32x32.png"));
	//map_size_camera_bounds->setText("Size&&Camera\nBounds");
	//map_section->addWidget(map_size_camera_bounds);

	map_tab->addSection(map_section);

	// Tools tab
	QRibbonTab* tools_tab = new QRibbonTab;

	// Import
	QRibbonSection* import_section = new QRibbonSection;
	import_section->setText("导入");

	import_heightmap->setIcon(QIcon("data/icons/ribbon/heightmap32x32.png"));
	import_heightmap->setText("导入\n高度图");
	import_section->addWidget(import_heightmap);

	tools_tab->addSection(import_section);

	// Tileset
	QRibbonSection* tileset_section = new QRibbonSection;
	tileset_section->setText("地形纹理");

	change_tileset->setIcon(QIcon("data/icons/ribbon/tileset.png"));
	change_tileset->setText("更换\n地形纹理");
	tileset_section->addWidget(change_tileset);

	change_tile_pathing->setIcon(QIcon("data/icons/ribbon/tileset32x32.png"));
	change_tile_pathing->setText("更改地形\n路径");
	tileset_section->addWidget(change_tile_pathing);

	tools_tab->addSection(tileset_section);

	QRibbonSection* game_section = new QRibbonSection;
	game_section->setText("游戏");

	switch_warcraft->setIcon(QIcon("data/icons/ribbon/WarIII32x32.ico"));
	switch_warcraft->setText("更换\n游戏目录");
	game_section->addWidget(switch_warcraft);

	tools_tab->addSection(game_section);

	addTab(home_tab, "Home");
	addTab(view_tab, "View");
	addTab(map_tab, "Map");
	addTab(tools_tab, "Tools");

}

MainRibbon::~MainRibbon() {
}
