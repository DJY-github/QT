// NodeBase.h: interface for the CNodeBase class.
// ���壺�����װ�����豸��װ�õĽڵ����
// ���ߣ�liuyuananfang 2013-03-19
//////////////////////////////////////////////////////////////////////
#ifndef NODEBASE_H
#define NODEBASE_H

#define NODE_TYPE_MAC_MANAGER (0) //���ͣ��豸������
#define NODE_TYPE_MAC (1) //���ͣ��豸
#define NODE_TYPE_AA (2) //���ͣ��豸�¹���װ��
#define NODE_TYPE_AA_CHILD (3) //���ͣ���װ���¹�װ��
#define NODE_TYPE_BB (4) //���ͣ�
#define NODE_TYPE_BB_CHILD (5) //���ͣ�
#define NODE_TYPE_CC (6) //���ͣ�
#define NODE_TYPE_CC_CHILD (7) //���ͣ�
#define NODE_TYPE_CC_CHILD_CHILD (8) //���ͣ�
#define NODE_TYPE_FINAL (9) //���ͣ��ն˽ڵ�

#define MAX_LEN_NODE_NAME (40)  //�ڵ�������󳤶�

#define CHECKBOX_UNCHECKED	      (0)	//δѡȡ
#define CHECKBOX_CHECKED		  (1)	//ȫѡȡ
#define CHECKBOX_PARTIALLYCHECKED (2)	//����ѡȡ

#include <string.h>
#include <stdio.h>

class CNodeBase
{
public:
    CNodeBase(CNodeBase *parent = NULL);
    ~CNodeBase();
    int setName(const char *name);
    int getName(char ch[],int len);
    const char *getName();

    virtual int getChildCount();
    virtual CNodeBase* getChildDevice(int index);

    void setParent(CNodeBase *pParent);
    CNodeBase * getParent();
    int getNodeType();
    void setType(int type);

    int isChecked(){return m_checked;}
    void setCheckState(int state){m_checked = state;}
protected:
    char m_name[MAX_LEN_NODE_NAME];
    int m_type;
    CNodeBase *m_pParent;

    int m_checked;
    int m_childCount;
};

#endif // NODEBASE_H
