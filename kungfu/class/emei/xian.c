// xian.c ����ʦ̫
// Modified By That Oct.1997
#include <command.h>
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_for_join();

void create()
{
	set_name("����ʦ̫", ({ "jingxian shitai","jingxian","shitai"}));
	set("long", "����һλ������ҵ��ã��������ۣ��������������ϣ�üĿ֮����һ�����֮����\n");
	set("gender", "Ů��");
	set("age", 45);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("shen", 10000);
	set("class", "bonze");
	set("inquiry",([
		"���" : (: ask_for_join :),
		"����" : (: ask_for_join :),
		"����" : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
	]));

	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("per", 20);

	set("max_qi", 1500);
	set("max_jing", 500);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jingli", 1500);
	set("max_jingli", 1500);

	set("combat_exp", 150000);
	set("score", 1000);
	set_skill("persuading", 80);
	set_skill("throwing", 70);
	set_skill("force", 70);
	set_skill("dodge", 70);
	set_skill("finger", 60);
	set_skill("parry", 70);
	set_skill("strike", 65);
	set_skill("blade", 60);
	set_skill("mahayana", 60);
	set_skill("literate", 60);
	set_skill("jinding-zhang", 90);
	set_skill("tiangang-zhi", 90);
	set_skill("yanxing-dao", 90);
	set_skill("zhutian-bu", 100);
	set_skill("linji-zhuang", 70);
	map_skill("force","linji-zhuang");
	map_skill("finger","tiangang-zhi");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("blade","yanxing-dao");
	map_skill("parry","yanxing-dao");
	prepare_skill("strike", "jinding-zhang");
	prepare_skill("finger", "tiangang-zhi");
	set("env/wimpy", 60);
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
//		(: perform_action, "sword.mie" :),
		(: perform_action, "blade.wuxing" :),
//		(: perform_action, "strike.bashi" :),
		(: perform_action, "finger.lingkong" :),		
		(: exert_function, "powerup" :),				
		(: exert_function, "recover" :),
		(: exert_function, "regenerate" :),
	}) );

	create_family("������", 4, "����");

	setup();
	carry_object(WEAPON_DIR"gangdao")->wield();
	carry_object(CLOTH_DIR"ni-cloth")->wear();
	carry_object(CLOTH_DIR"ni-shoe")->wear();
}
void init()
{
	add_action("do_kneel", "kneel");
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("class")!="bonze" )
	{
		command("say �����ӷ�ƶ�᲻���׼ҵ��ӡ�ʩ������ѧ�տ�ȥ�����׼�ʦ�á�");
		return;
	}
	if( (string)ob->query("gender") != "Ů��" )
	{
		command("say �����ӷ�ƶ�᲻���е��ӡ�ʩ������ѧ�տ�ȥ�����׼�ʦ�á�");
		return;
	}
	if ((int)ob->query("shen") < 100)
	{
		command("say " + RANK_D->query_respect(ob) + "����������֮�»����Ĳ�����");
		return;
	}
	command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
	command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������");
	command("recruit " + ob->query("id"));
}
#include "emei.h"