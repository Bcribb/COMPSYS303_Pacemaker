/*****************************************************************************/
/*                 G E N E R A T E D       C    C O D E                      */
/*****************************************************************************/
/* KIELER - Kiel Integrated Environment for Layout Eclipse RichClient        */
/*                                                                           */
/* http://www.informatik.uni-kiel.de/rtsys/kieler/                           */
/* Copyright 2014 by                                                         */
/* + Kiel University                                                         */
/*   + Department of Computer Science                                        */
/*     + Real-Time and Embedded Systems Group                                */
/*                                                                           */
/* This code is provided under the terms of the Eclipse Public License (EPL).*/
/*****************************************************************************/
char ERROR;
char VPase;
char VSense;
char LRITO;
char VRPTO;
char _Assignment2_local_LRI_stop;
char _Assignment2_local_VRP_stop;
char _Assignment2_local_LRI_start;
char _Assignment2_local_LRI_ex;
char _Assignment2_local_VRP_start;
char _Assignment2_local_VRP_ex;
char g0;
char g1;
char g2;
char g3;
char PRE_g3;
char g4;
char g5;
char g6;
char g7;
char PRE_g7;
char g8;
char g9;
char g10;
char g11;
char g12;
char PRE_g12;
char g13;
char g14;
char g15;
char g16;
char g17;
char PRE_g17;
char g18;
char g19;
char g20;
char g21;
char g22;
char g23;
char PRE_g23;
char g24;
char g25;
char g26;
char g27;
char PRE_g27;
char g28;
char g29;
char g30;
char g31;
char g32;
char g33;
char PRE_g33;
char g34;
char g35;
char g36;
char g37;
char g38;
char PRE_g38;
char g39;
char g40;
char g41;
char PRE_g41;
char g42;
char g43;
char g44;
char g45;
char PRE_g45;
char g46;
char g47;
char g48;
char g49;
char g50;
char g51;
char PRE_g51;
char g52;
char g53;
char g54;
char g55;
char PRE_g55;
char g56;
char g57;
char g58;
char g59;
char PRE_g59;
char g60;
char g61;
char g62;
char _GO;
char _cg6;
char _cg4;
char _cg8;
char _cg9;
char _cg20;
char _cg21;
char _cg13;
char _cg18;
char _cg15;
char _cg19;
char _cg31;
char _cg26;
char _cg24;
char _cg28;
char _cg29;
char _cg36;
char _cg34;
char _cg39;
char _cg42;
char _cg46;
char _cg40;
char _cg48;
char _cg43;
char _cg52;
char g5_e1;
char g14_e2;
char g25_e3;
char g35_e4;
char g53_e5;
char g57_e1;
char g61_e2;
int _PRE_GO;
void reset(){
   _GO = 1;
   _PRE_GO = 0;
   PRE_g3 = 0;
   PRE_g7 = 0;
   PRE_g12 = 0;
   PRE_g17 = 0;
   PRE_g23 = 0;
   PRE_g27 = 0;
   PRE_g33 = 0;
   PRE_g38 = 0;
   PRE_g41 = 0;
   PRE_g45 = 0;
   PRE_g51 = 0;
   PRE_g55 = 0;
   PRE_g59 = 0;
   return;
}
void tick(){
   if(_PRE_GO == 1){
      _GO = 0;
   }
   {
      g0 = _GO;
      g1 = g0;
      g2 = g1;
      g50 = g1;
      g52 =(PRE_g51);
      _cg52 = ERROR;
      g51 =(g50||(g52&&(!(_cg52))));
      if(g51){
         _Assignment2_local_LRI_start = 0;
         _Assignment2_local_LRI_ex = 0;
         _Assignment2_local_LRI_stop = 0;
         _Assignment2_local_VRP_start = 0;
         _Assignment2_local_VRP_ex = 0;
         _Assignment2_local_VRP_stop = 0;
      }
      g8 =(PRE_g7);
      _cg8 = ERROR;
      g9 =(g8&&(!(_cg8)));
      _cg9 = VRPTO;
      g10 =(g9&&_cg9);
      if(g10){
         _Assignment2_local_VRP_ex =(_Assignment2_local_VRP_ex||1);
      }
      g60 =(PRE_g59);
      g58 = g0;
      g59 =(g60||g58);
      if(g59){
         VPase = 0;
      }
      g28 =(PRE_g27);
      _cg28 = ERROR;
      g29 =(g28&&(!(_cg28)));
      _cg29 = LRITO;
      g30 =(g29&&_cg29);
      if(g30){
         _Assignment2_local_LRI_ex =(_Assignment2_local_LRI_ex||1);
      }
      g42 =(PRE_g41);
      _cg42 = ERROR;
      g43 =(g42&&(!(_cg42)));
      _cg43 = VSense;
      g48 =(g43&&(!(_cg43)));
      _cg48 = _Assignment2_local_LRI_ex;
      g49 =(g48&&_cg48);
      if(g49){
         VPase =(VPase||1);
      }
      g13 =(PRE_g12);
      _cg13 = ERROR;
      g15 =(g13&&(!(_cg13)));
      _cg15 = VSense;
      g21 =(g15&&(!(_cg15)));
      _cg21 = VPase;
      g16 =((g21&&_cg21)||(g15&&_cg15));
      if(g16){
         _Assignment2_local_VRP_start =(_Assignment2_local_VRP_start||1);
      }
      g4 =(PRE_g3);
      _cg4 = ERROR;
      g6 =(g4&&(!(_cg4)));
      _cg6 = _Assignment2_local_VRP_start;
      g3 =(g2||g10||(g6&&(!(_cg6))));
      g5 =((g8&&_cg8)||(g4&&_cg4));
      g7 =((g6&&_cg6)||(g9&&(!(_cg9))));
      g11 = g1;
      g18 =(PRE_g17);
      _cg18 = ERROR;
      g19 =(g18&&(!(_cg18)));
      _cg19 = VSense;
      g20 =(g19&&(!(_cg19)));
      _cg20 = _Assignment2_local_VRP_ex;
      g12 =((g20&&_cg20)||(g21&&(!(_cg21)))||g11);
      g14 =((g13&&_cg13)||(g18&&_cg18));
      g17 =(g16||(g20&&(!(_cg20)))||(g19&&_cg19));
      g22 = g1;
      g44 =(g43&&_cg43);
      if(g44){
         _Assignment2_local_LRI_stop =(_Assignment2_local_LRI_stop||1);
      }
      g31 =(g29&&(!(_cg29)));
      _cg31 = _Assignment2_local_LRI_stop;
      g34 =(PRE_g33);
      _cg34 = ERROR;
      g36 =(g34&&(!(_cg34)));
      _cg36 = VSense;
      g37 =(g36&&_cg36);
      if(g37){
         _Assignment2_local_LRI_start =(_Assignment2_local_LRI_start||1);
      }
      g46 =(PRE_g45);
      _cg46 = ERROR;
      g47 =(g46&&(!(_cg46)));
      if(g47){
         _Assignment2_local_LRI_start =(_Assignment2_local_LRI_start||1);
      }
      g24 =(PRE_g23);
      _cg24 = ERROR;
      g26 =(g24&&(!(_cg24)));
      _cg26 = _Assignment2_local_LRI_start;
      g23 =(g30||(g31&&_cg31)||g22||(g26&&(!(_cg26))));
      g25 =((g24&&_cg24)||(g28&&_cg28));
      g27 =((g31&&(!(_cg31)))||(g26&&_cg26));
      g32 = g1;
      g33 =(g32||(g36&&(!(_cg36))));
      g39 =(PRE_g38);
      _cg39 = ERROR;
      g35 =((g42&&_cg42)||(g34&&_cg34)||(g39&&_cg39)||(g46&&_cg46));
      g40 =(g39&&(!(_cg39)));
      _cg40 = _Assignment2_local_VRP_ex;
      g38 =((g40&&(!(_cg40)))||g47||g37);
      g41 =((g40&&_cg40)||(g48&&(!(_cg48))));
      g45 =(g44||g49);
      g53 =(g52&&_cg52);
      g5_e1 =(!((g4||g8)));
      g14_e2 =(!((g13||g18)));
      g25_e3 =(!((g24||g28)));
      g35_e4 =(!((g34||g39||g42||g46)));
      g53_e5 =(!(g52));
      g54 =((g5_e1||g5)&&(g14_e2||g14)&&(g25_e3||g25)&&(g35_e4||g35)&&(g53_e5||g53)&&(g5||g14||g25||g35||g53));
      g56 =(PRE_g55);
      g55 =(g56||g54);
      g57_e1 =(!((g4||g13||g24||g34||g8||g28||g56||g18||g39||g52||g42||g46)));
      g61_e2 =(!(g60));
   }
   PRE_g3 = g3;
   PRE_g7 = g7;
   PRE_g12 = g12;
   PRE_g17 = g17;
   PRE_g23 = g23;
   PRE_g27 = g27;
   PRE_g33 = g33;
   PRE_g38 = g38;
   PRE_g41 = g41;
   PRE_g45 = g45;
   PRE_g51 = g51;
   PRE_g55 = g55;
   PRE_g59 = g59;
   _PRE_GO = _GO;
   return;
}
