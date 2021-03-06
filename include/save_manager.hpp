#pragma once
/**
 * @file save_manager.hpp
 * @brief Save Manager
 */
#ifndef SAVE_MANAGER_HPP
#define SAVE_MANAGER_HPP

#include "save.hpp"

class SaveManager
{
	public:
		GameVersion version;

		savebuffer_t savebuffer;
		bankbuffer_t bankbuffer;
		savedata_s savedata;
		bankdata_s bankdata;
		bool dev;

	public:
		/* PC Offsets */
		saveConst_t offsetTrainerCard;
		saveConst_t offsetPCLayout;
		saveConst_t offsetPCBackground;
		saveConst_t offsetPC;

		/* BK Offsets */
		saveConst_t offsetBK;
		saveConst_t offsetBKLayout;
		saveConst_t offsetBKBackground;
		saveConst_t offsetWonderBox;

		/* Global const */
		saveConst_t sizeSave;
		saveConst_t sizeBank;

	public:
		SaveManager(void);
		~SaveManager(void);

		Result load(void);
		Result save(void);
		Result backupFile(void);

		void setGame(u32 bytesRead);
		void setGameOffsets(void);
		void setBank(u32 bytesRead);
		void setBankOffsets(void);

		bool isPkmEmpty(pkm_s* pkm);
		bool isSlotEmpty(u16 boxId, u16 slotId, bool inBank);
		box_s* countBox(u16 boxId, bool inBank);
		box_s* getWBox(void);
		box_s* getBox(u16 boxId, bool inBank);
		pkm_s* getWPkm(u16 slotId);
		pkm_s* getPkm(u16 slotId, bool inBank);
		pkm_s* getPkm(u16 boxId, u16 slotId, bool inBank);
		bool movePkm(pkm_s* src, pkm_s* dst);
		bool movePkm(pkm_s* src, pkm_s* dst, bool srcBanked, bool dstBanked);
		bool pastePkm(pkm_s* src, pkm_s* dst);
		bool pastePkm(pkm_s* src, pkm_s* dst, bool srcBanked, bool dstBanked);
		void moveBox(u16 boxId_1, bool inBank_1, u16 boxId_2, bool inBank_2);
		bool filterPkm(pkm_s* pkm, bool toBank, bool fromBank);

		void addDex(pkm_s* pkm);
		void tradePkm(pkm_s* pkm);
		void tradePkmHT(pkm_s* pkm);


		void decryptEk6(pkm_s* pkm);
		void encryptPk6(pkm_s* pkm);
		void shufflePk6(pk6_t* pk6, u8 sv);
		void rewriteSaveCHK(void);

		u32 LCRNG(u32 seed);
		u32 CHKOffset(u32 i);
		u32 CHKLength(u32 i);
		u16 ccitt16(u8* data, u32 len);

	private:

		Result loadFile(void);
		Result saveFile(void);

		Result loadSaveFile(void);
		Result loadBankFile(void);
		Result saveSaveFile(void);
		Result saveBankFile(void);
		Result backupSaveFile(void);
		Result backupBankFile(void);

		// Load Data
		void loadData(void);
		void loadSaveData(void);
		void loadBankData(void);
		// Load Pokemon (pkm_s)
		//   To <- From
		pkm_s* loadPkmPC(u16 boxId, u16 slotId);
		pkm_s* loadPkmBK(u16 boxId, u16 slotId);
		pkm_s* loadPkmWBK(u16 slotId);
		void loadEk6PC(pkm_s* pkm, u32 offsetSlot);
		void loadEk6BK(pkm_s* pkm, u32 offsetSlot);
		void loadEk6WBK(pkm_s* pkm, u32 offsetSlot);
		void loadPk6Ek6(pkm_s* pkm);
		void loadPkmPk6(pkm_s* pkm);

		// Save Data
		void saveData(void);
		void saveSaveData(void);
		void saveBankData(void);
		// Save Pokemon (pkm_s)
		//   From -> To
		void savePkmPC(u16 boxId, u16 slotId);
		void savePkmBK(u16 boxId, u16 slotId);
		void saveEk6PC(pkm_s* pkm);
		void saveEk6BK(pkm_s* pkm);
		void savePk6Ek6(pkm_s* pkm);
		void savePkmPk6(pkm_s* pkm);
};

#endif // SAVE_MANAGER_HPP
