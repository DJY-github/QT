#include "NodeBase.h"

/*********************************************************************
���ܣ����캯��
������parent��ָ�򸸽ڵ�
���أ���
���ߣ�liuyuananfang  2013-03-19
*********************************************************************/
CNodeBase::CNodeBase(CNodeBase *parent)
{
    memset(m_name,0,sizeof(m_name));
    m_pParent = parent;

    m_checked = false;
    m_childCount = 0;
}

/*********************************************************************
���ܣ���������
��������
���أ���
���ߣ�liuyuananfang  2013-03-19
*********************************************************************/
CNodeBase::~CNodeBase()
{
}

/*********************************************************************
���ܣ����ýڵ�����
������name���ڵ�������
���أ�<0��ʧ�ܡ�-1����������Ƿ�
     >0���ɹ�
���ߣ�liuyuananfang  2013-03-19
*********************************************************************/
int CNodeBase::setName(const char *name)
{
    if(NULL == name)  return -1;
    memset(m_name,0,MAX_LEN_NODE_NAME);
    memcpy(m_name,name,strlen(name));
    return 1;
}

/*********************************************************************
���ܣ���ȡ�ڵ�����
������ch��������������Žڵ�����
     len,ch������ڴ��С
���أ�<0��ʧ�ܡ�-1����������Ƿ�
     >0���ɹ�
���ߣ�liuyuananfang  2013-03-19
*********************************************************************/
int CNodeBase::getName(char ch[], int len)
{
    if(NULL == ch)  return -1;
    if(len < MAX_LEN_NODE_NAME) return -1;

    memcpy(ch,m_name,MAX_LEN_NODE_NAME);
    return 1;
}

const char * CNodeBase::getName()
{
    return m_name;
}

int CNodeBase::getChildCount()
{
    return m_childCount;
}

CNodeBase *CNodeBase::getChildDevice(int index)
{
    return NULL;
}

void CNodeBase::setParent( CNodeBase *pParent )
{
	m_pParent = pParent;
}

CNodeBase * CNodeBase::getParent()
{
	return m_pParent;
}

int CNodeBase::getNodeType()
{
    return m_type;
}

void CNodeBase::setType(int type)
{
    m_type = type;
}
