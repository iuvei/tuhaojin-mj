#pragma once
#include "cocos2d.h"
#include "Platform/PlatformHeader.h"
#include "Kernel/network/CSocketMission.h"

//////////////////////////////////////////////////////////////////////////
// 用户资料修改结构
//////////////////////////////////////////////////////////////////////////
struct tagModifyIndividual
{
	tagModifyIndividual()
	{
		memset(this,0,sizeof(tagModifyIndividual));
	}
	// 性别
	uint8 cbGender;
	//用户昵称
	char szNickName[LEN_NICKNAME];
	//个性签名
	char szUnderWrite[LEN_UNDER_WRITE];
	//用户备注
	char szUserNote[LEN_USER_NOTE];
	//真实名字
	char szCompellation[LEN_COMPELLATION];
	//固定号码
	char szSeatPhone[LEN_SEAT_PHONE];
	//手机号码
	char szMobilePhone[LEN_MOBILE_PHONE];
	//Q Q 号码
	char szQQ[LEN_QQ];
	//电子邮件
	char szEMail[LEN_EMAIL];
	//详细地址
	char szDwellingPlace[LEN_DWELLING_PLACE];
	//头像HTTP
	char szHeadHttp[LEN_USER_NOTE];
	//渠道号
	char szUserChannel[LEN_NICKNAME];
};


//////////////////////////////////////////////////////////////////////////
// 用户资料修改提示
//////////////////////////////////////////////////////////////////////////
class IGPIndividualMissionSink
{
public:
	virtual ~IGPIndividualMissionSink(){}
	virtual void onGPIndividualInfo(int type){}
	virtual void onGPAccountInfo(CMD_GP_UserAccountInfo* pAccountInfo){}
	virtual void onGPAccountInfoHttpIP(dword dwUserID, std::string strIP,std::string strHttp){}
	virtual void onGPIndividualSuccess(int type, const char* szDescription){}
	virtual void onGPIndividualFailure(int type, const char* szDescription){}
};

//////////////////////////////////////////////////////////////////////////
// 用户资料修改任务
//////////////////////////////////////////////////////////////////////////
class CGPIndividualMission
	: public CSocketMission
{
public:
	enum Type
	{
		MISSION_INDIVIDUAL_NULL,
		MISSION_INDIVIDUAL_QUERY,
		MISSION_INDIVIDUAL_Account,
		MISSION_INDIVIDUAL_MODIFY,
		MISSION_INDIVIDUAL_SPREADER,
	};
public:
	CGPIndividualMission(const char* url, int port);
	// 设置回调接口
	void setMissionSink(IGPIndividualMissionSink* pIGPIndividualMissionSink);

	// 查询个人资料
	void query(int iAccountID,bool bRecStop = true);

	// 查询个人资料
	void queryAccountInfo(int iAccountID = -1);

	void modifyName(std::string kName);

	void modifyGender(byte gender);

	void modify(std::string kNickName,byte gender);

	void modify(const tagModifyIndividual& individual);
	// 修改推广人
	void modifySpreader(std::string kSpreaderID);
	// 修改头像http
	void modifyHeadHttp(std::string kHttp);
	// 渠道号
	void modifyUserChannel(std::string szUserChannel);

	void modifyPhoneNumber(std::string kPhoneNumber);

	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	// 子消息处理
private:
	// 个人信息
	bool onSubUserAccountInfo(void* data, int size);
	// 个人信息
	bool onSubUserIndividual(void* data, int size);
	// 设置推荐人
	bool onSubSpreaderResoult(void* data, int size);
	// 操作成功
	bool onSubOperateSuccess(void* data, int size);
	// 操作失败
	bool onSubOperateFailure(void* data, int size);
	
private:
	bool m_bRevStop;
	// 任务类型
	uint8 mMissionType;

	dword mAccountInfoID;

	std::string m_kSpreaderID;

	std::string m_kHeadHttp;
	// 回调
	IGPIndividualMissionSink* mIGPIndividualMissionSink;

	//////////////////////////////////////////////////////////////////////////
	// 修改个人资料
	//////////////////////////////////////////////////////////////////////////
	tagModifyIndividual mModifyIndividual;
}; // CGPIndividualMission
