// mishi2.c 密室
// Java Oct.10 1998

inherit ROOM;

void create()
{
	set("short", "密室");
	set("long", @LONG
这里是古墓中的密室，四周密不透风，你只能借着墙上昏暗的灯光
来勉强分辨方向。墙是用整块的青石砌合起来的，接合的甚是完美，你
难以从中找出一丝缝隙。墙上好象雕有一些花纹。
LONG	);
	set("exits", ([
		"east"  : __DIR__"mishi3",
		"west"  : __FILE__,
		"north" : __FILE__,
		"south" : __DIR__"mishi1",
	]));
	set("no_clean_up", 0);
	set("coor/x", -3200);
	set("coor/y", 30);
	set("coor/z", 100);
	setup();
	replace_program(ROOM);
}
