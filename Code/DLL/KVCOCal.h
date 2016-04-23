#ifndef _KVCO_H_
#define _KVCO_H_
#include "IFHandler.h"
class CKVCOCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CKVCOCal)
public: 

		CKVCOCal();
		~CKVCOCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;

private:
     IntVtr m_vChannelList_850;
	 IntVtr m_vChannelList_900;
	 IntVtr m_vChannelList_1800;
	 IntVtr m_vChannelList_1900;
	 int m_iNumTxCycles;
	 int m_iNumMeas;
	 IntVtr m_ivRFmodeList;
	 IntVtr m_ivChannelList;
	 IntVtr m_ivKVCOminLimit;
	 IntVtr m_ivKVCOmaxLimit;

     

private: 
	bool CKVCOCalMainFunc();
	bool CKVCOCal_V2();
	bool CKVCOCalFunc_850();
	bool CKVCOCalFunc_900();
	bool CKVCOCalFunc_1800();
	bool CKVCOCalFunc_1900();

	bool CKVCOCalBandSelect(int iBand);





 
};
#endif