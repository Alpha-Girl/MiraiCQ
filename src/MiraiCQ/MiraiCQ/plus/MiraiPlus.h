#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <shared_mutex>
#include <atomic>

class MiraiPlus
{
public:

	struct PlusDef
	{
		struct Event
		{
			int type;
			void* function = 0;
			int priority = 30000;
			std::string fun_name;
		};
		struct Menu
		{
			std::string name;
			void* function = 0;
		};
		void * module_hand = 0; /* dllģ��ľ�� HMODULE */
		std::string name; /* ������� */
		std::string filename; /* ������ļ��� */
		std::string version; /* ����汾 */
		std::string author; /* ������� */
		std::string description; /* ������� */
		int ac; /* ���ac */
		std::vector<std::shared_ptr<const Event>> event_vec;
		std::vector<std::shared_ptr<const Menu>> menu_vec;
		std::set<int> auth_vec;
		std::atomic_bool is_enable = false; /* ����Ƿ����� */
		std::atomic_bool is_first_enable = true; /* ��һ��������Ҫ���ÿ�������¼� */
		~PlusDef();
		/*
		* �������Ӳ���л��һ��Event
		* ����`type`��������type��
		* ����ֵ���ɹ�����Event��ʧ�ܷ���null
		*/
		const std::shared_ptr<const Event> get_event_fun(int type)noexcept;

		/*
		* �������Ӳ���л��Menu����
		* ����ֵ���ɹ�����Menu���飬����ʧ��
		*/
		std::vector<std::shared_ptr<const Menu>> get_menu_vec() noexcept;

		/*
		* ��������ò������
		* ����ֵ�����ز������
		*/
		std::string get_name() noexcept;

		/*
		* ��������ò������
		* ����ֵ�����ز������
		*/
		std::string get_filename() noexcept;
	};

	~MiraiPlus();

	/*
	* ����������һ��dll���
	* ����`dll_name`:dll���֣�������׺��
	* ����`err_msg`,����ʧ��ʱ˵��ԭ��
	* ����ֵ���ɹ�����`true`,ʧ�ܷ���`false`
	*/
	bool load_plus(const std::string& dll_name,std::string & err_msg) noexcept;

	/*
	* ����������һ�����
	* ����`ac`:������
	* ����`err_msg`,����ʧ��ʱ˵��ԭ��
	* ����ֵ�����غ���ִ�к����Ƿ�����
	*/
	bool enable_plus(int ac,std::string & err_msg) noexcept;

	/*
	* ����������һ�����
	* ����`ac`:������
	* ����`err_msg`,����ʧ��ʱ˵��ԭ��
	* ����ֵ�����غ���ִ�к����Ƿ񱻽���
	*/
	bool disable_plus(int ac, std::string & err_msg) noexcept;

	/*
	* �������ж�һ������Ƿ�����
	* ����`ac`:������
	* ����ֵ���Ѿ������÷���`true`��δ���û���ac���󷵻�false
	*/
	bool is_enable(int ac) noexcept;

	/*
	* ������ж��һ�����
	* ����`ac`:������
	* ����`err_msg`,ж��ʧ��ʱ˵��ԭ��
	* ����ֵ�����غ���ִ�к����Ƿ�ж��
	*/
	bool del_plus(int ac) noexcept;

	/*
	* ������ͨ��AC�����һ�����
	* ����`ac`:������
	* ����ֵ���ɹ����ز��ָ�룬ac��Ч����null
	*/
	std::shared_ptr<PlusDef> get_plus(int ac) noexcept;

	/*
	* ��������ò��map
	* ����ֵ�����ز��mapָ�룬�˺�������ʧ��
	*/
	std::map<int, std::shared_ptr<PlusDef>> get_all_plus() noexcept;

	/*
	* ��������ò��ac
	* ����ֵ������ac���飬�˺�������ʧ��
	*/
	std::vector<std::pair<int, std::weak_ptr<MiraiPlus::PlusDef>>> get_all_ac() noexcept;

	static MiraiPlus* get_instance() noexcept;
private:
	MiraiPlus();
	std::map<int, std::shared_ptr<PlusDef>> plus_map;
	std::shared_mutex mx_plus_map;

};

