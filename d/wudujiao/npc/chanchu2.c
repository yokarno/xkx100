// chanchu2.c
inherit NPC;
#include <ansi.h>

void create()
{
        set_name("莽牯朱蛤",({"chan chu"}));

        set("race", "野兽");
        set("long", "一只拳头大小，叫声洪亮的毒蛤蟆。\n");
        set("age", 1000);
        set("attitude", "peaceful");

        set("max_jing", 500);
        set("max_qi", 500);

        set("str", 30);
        set("con", 50);

        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 70);
        set_skill("unarmed",80);
        set_skill("parry",80);
        set_skill("dodge",80);
        set_skill("force",80);

        set("combat_exp", 150000);
        set_weight(5000);

        setup();
}
int init()
{
        object me,who;
        ::init();
        who = this_object();
        if (interactive(me = this_player()))
        {
                if (me->query("id")==who->query_temp("kill_name"))
                {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, me);
                }
        }
        add_action("do_attack","gong");
        add_action("do_stop","ting");
        add_action("do_sha","sha");
        add_action("do_guard","baohu");
        add_action("do_hit","hit");
        add_action("do_hit","kill");
        add_action("do_hit","touxi");
//      remove_call_out("do_baohu");
//      call_out("do_baohu",5);

}
int hit_ob(object me, object ob, int damage)
{
        if ((string)ob->query("family/family_name") != "五毒教") {
                ob->apply_condition("chanchu_poison", 20
              +(int)ob->query_condition("chanchu_poison") );
              tell_object(ob, HIG "你觉得被咬中的地方一阵麻木！\n" NOR );
        }
}
void die()
{
        object ob;
        message_vision("$N倒在地上，死了！\n", this_object());
        ob=new(__DIR__"obj/chanchudu.c");
        ob->move(environment(this_object()));
        destruct(this_object());

//       return 1;
//      ::die();
}

#include "xunwu.h";

