//
// Created by user on 27.01.23.
//

#include "GameMode.h"
#include "../../src/hook.h"
#include "../../hybris/include/hybris/dlfcn.h"
#include "../level/BlockPos.h"
#include "../../src/common.h"
#include "../level/BlockSource.h"
#include "../statics.h"
#include "../network/packets/UpdateBlockPacket.h"
#include <iostream>
#include <cstring>
#include <packets/binary/BinaryStream.h>

void GameMode::initHooks(void *handle) {
    //std::cout << sizeof( NetworkIdentifier) << "\n";
    hookFunction((void *) hybris_dlsym(handle, "_ZN8GameMode9useItemOnER6PlayerR12ItemInstanceRK8BlockPosaRK4Vec3"), (void *) &GameMode::useItemOn, (void **) &GameMode::GameMode_useItemOn);
    hookFunction((void *) hybris_dlsym(handle, "_ZN8GameMode7useItemER6PlayerR12ItemInstance"), (void *) &GameMode::useItem, (void **) &GameMode::GameMode_useItem);
}

bool GameMode::useItemOn(Player &p, ItemInstance &i, const BlockPos &pos, char c, const Vec3 &vec) {
    std::cout << pos.x << " " << pos.y << " " << pos.z << "\n";
    std::cout << vec.x << " " << vec.y << " " << vec.z << "\n";
    //std::cout << i.itemOrBlock << " " << i.someInt1  << " " << i.someInt3 << " " << i.someInt4 << "\n";

    if(i.itemOrBlock)
        std::cout << i.itemOrBlock->fullName << "/" << i.itemOrBlock->name << "/" << i.itemOrBlock->id << "/" << ((int) i.count) << "\n";
   // i.add(1);
    //p.addItem(i);
  // p.inventoryProxy->removeItem(0, 0, 0);
//    p.inventoryProxy->add(i, false);
   // auto is = p.getInventory();
    //is.removeItemInstance(&i);
    //if(i.itemOrBlock1)
    //std::cout << i.itemOrBlock1->fullName << "/" << i.itemOrBlock1->name << "\n";
  // i.remove(i.count);

  //p.getInventory().clearInventory(1);
   //p.inventoryProxy->removeItem(0,2,0);
    //std::cout << p.inventoryProxy->inventory->getComplexItems().size() << "\n";


   // auto tt = p.inventoryProxy->getSelectedSlot();m
    std::cout << "count is " << (int) p.inventoryProxy->getSlots()[p.inventoryProxy->selectedSlot]->count << "\n";
    auto bs = BlockSource(*p.getLevel(), *p.getDimension(), *p.getDimension()->getChunkSource(), true, false);
    //std::cout << (int) bs.getBlockID(pos)<< " is block tapped\n";
  //  auto cb = bs.getBlockID(pos);
    auto tt = bs.getBlockAndData(pos);
    /*p.sendMessage("Нажал на " + bs.getBlock(pos)->blockName);
    p.sendMessage("Ид " + std::to_string((int)bs.getBlock(pos)->blockId));
    p.sendMessage("Ид getBlockID " + std::to_string((int)bs.getBlockID(pos).id));
    p.sendMessage("Ид getBlockAndData " + std::to_string((int)tt.id));
    p.sendMessage("Позиция: " + pos.toString());
    p.sendMessage("Дата: " + std::to_string((int) tt.data));*/

    auto r = GameMode_useItemOn(this,p,i,pos,c,vec);
    //p.sendInventory();
    return r;
    //sleep(9999);
   // p.sendMessage("Флаги: " + std::to_string((int) bs.getBlockAndData(pos).flags));


    FullBlock fb {
            .blockIdAndData = new BlockIDAndData {
                    .id = 54,
                    .data = 0
            }
    };
   for(int ii= 1; ii<= 10; ii++) {
       bs.setBlockAndData({pos.x, pos.y + ii, pos.z}, fb, 0, nullptr);
        BinaryStream bss;
                bss.putByte(0x16);
                bss.putSVarInt(pos.x);
                bss.putUVarInt(pos.y + ii);
                bss.putSVarInt(pos.z);
                bss.putUVarInt((int) fb.blockIdAndData->id);
                bss.putUVarInt(((0b0001 | 0b0010) << 4) | (int) fb.blockIdAndData->data);
                statics::serverNetworkHandler->networkHandler->getPeerForUser(p.identifier)->sendPacket(bss.getBuffer(),1,0);

   }
   // p.inventoryProxy->getSlots()[p.inventoryProxy->selectedSlot]->count++;
   /* for(auto ss : p.inventoryProxy->getSlots()) {
        std::cout << ss->itemOrBlock << " is iob\n";
       // ss->itemOrBlock->id = 35;
       // ss->damageOrAux = ii;
       // ss->count = 1;
       if(ss->count == 0) {
           ss->_setItem(35);
           ss->damageOrAux = (short) ii;
           ss->count = 2;
           std::cout << ss->itemOrBlock->id << " " << ss->itemOrBlock->name << ss->itemOrBlock->fullName << " / " << ss->damageOrAux << "\n";
       }
       if(ii++ > 15)
           ii = 0;
       // std::cout << (int) ss->count << "\n";
       // if(ss->count > 0)
       //     ss->count = 2;
       // ss->itemOrBlock = (BlockItem *) (new ItemInstance(35, 1, ii));
    }*/
    //return false;
    //handleSignal(11,0);

}

bool GameMode::useItem(Player &p, ItemInstance &i) {
    std::cout << "useItem\n";
    return GameMode_useItem(this, p, i);
}
