@echo off

make lib
make clean
make all MAXPOINTCNT=5 PASSWORD_EN=1 DEBUG_EN=0 EN_CRP=2 OEM=0
make clean


@echo ===========================================================
@echo [按任意键退出]
@pause>nul
@exit