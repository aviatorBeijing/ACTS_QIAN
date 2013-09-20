// testTraderApi.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "ThostFtdcTraderApi.h"
#include "TraderSpi.h"
#include "PgsqlConfig.h"

// UserApi����
CThostFtdcTraderApi* pUserApi;

// ���ò���

CPgsqlConfig g_PgsqlConfig;

TThostFtdcInstrumentIDType INSTRUMENT_ID = "cu0909";		// ��Լ����
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;		// ��������
TThostFtdcPriceType	LIMIT_PRICE = 38850;			// �۸�

// ������
int iRequestID = 0;

int main(void)
{
	g_PgsqlConfig.InitializeConfig();
	// ��ʼ��UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();				// ����UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);				// ע���¼���
	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);				// ע�ṫ����
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);				// ע��˽����
	pUserApi->RegisterFront(const_cast<char*>(g_PgsqlConfig.GetFrontAddress().c_str()));	// connect
	pUserApi->Init();

	pUserApi->Join();
	pUserApi->Release();
	return 0;
}
