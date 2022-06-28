#include"Reflection.h"


Reflection::Reflection()
{
}

//ͨ���������ַ�����ȡ���ʵ��
void* Reflection::getClassByName(std::string className)
{
    std::map<std::string, PTRCreateObject>::const_iterator iter;
    iter = m_classMap.find(className);
    if (iter == m_classMap.end())
    {
        return NULL;
    }
    else
    {
        return iter->second();
    }
}

//���������������ַ����Ͷ�Ӧ�Ĵ��������ĺ������浽map��   
void Reflection::registClass(std::string name, PTRCreateObject method)
{
    m_classMap.insert(std::pair<std::string, PTRCreateObject>(name, method));
}