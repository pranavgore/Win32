#pragma once

const TCHAR *CPUVendor[] = { TEXT("Select the component"), TEXT("Intel"), TEXT("AMD"), NULL };
const TCHAR *IntelSubType[] = { TEXT("Select the component"), TEXT("Core i3"), TEXT("Core i5"), TEXT("Core i7"), TEXT("Core i9"), TEXT("Pentium"), TEXT("Xeon"), NULL };
const TCHAR *AMDSubType[] = { TEXT("Select the component"), TEXT("Ryzen 3"), TEXT("Ryzen 5"), TEXT("Ryzen 7"), TEXT("Ryzen Threadripper"), TEXT("A Series APU"), TEXT("FX Series"), NULL };

const TCHAR *Corei3Models[] = { TEXT("Select the component"), TEXT("8100 3.60GHz"), TEXT("8350k 4.00GHz"), TEXT("7100 3.90GHz"), TEXT("6098P Dual Core 3.60GHz"), TEXT("6100 3.60GHz"), NULL };
const int Corei3Prices[] = { NULL, 9638, 14270, 8900, 8761, 9375, NULL };

const TCHAR *Corei5Models[] = { TEXT("Select the component"), TEXT("8400 2.80GHz"), TEXT("8600k 3.50GHz"), TEXT("7640X 4.0GHz"), TEXT("7600k 4.20GHz"), TEXT("7600 4.10GHz"), TEXT("7500 3.80GHz"), TEXT("7400 3.50GHz"), TEXT("6600 3.3GHz"), TEXT("6500 3.20GHz"), TEXT("6400 2.7GHz"), NULL };
const int Corei5Prices[] = { NULL, 15021, 21405, 18850, 19130, 16685, 15250, 13600, 18124, 16733, 14899, NULL };

const TCHAR *Corei7Models[] = { TEXT("Select the component"), TEXT("8700 3.20GHz"), TEXT("8700K 3.70GHz"), TEXT("7740X 4.30GHz"), TEXT("7800X 3.50GHz"), TEXT("7820X 3.60GHz"), TEXT("7700K 4.50GHz"), TEXT("7700 4.20GHz"), TEXT("6850K 3.80GHz"), TEXT("6950X 3.50GHz"), TEXT("6900K 3.70GHz"), TEXT("6800K 3.60GHz"), TEXT("4790K 4.00GHz"), NULL };
const int Corei7Prices[] = { NULL, 27163, 31544, 28548, 31220, 46999, 26100, 23300, 39599, 112750, 83215, 31268, 27307, NULL };

const TCHAR *Corei9Models[] = { TEXT("Select the component") , TEXT("7900X 3.30GHz"), NULL };
const int Corei9Prices[] = { NULL, 81843, NULL };

const TCHAR *PentiumModels[] = { TEXT("Select the component"), TEXT("G3250 Dual Core 3.20GHz"), TEXT("G4400 Dual Core 3.30GHz"), TEXT("G4560 Dual Core 3.50GHz"), NULL };
const int PentiumPrices[] = { NULL, 4966, 3800, 6700, NULL };

const TCHAR *XeonModels[] = { TEXT("Select the component"), TEXT("E3-1245 V5 3.50GHz"), TEXT("E3-1220 V5 3.0GHz"), TEXT("E5-2603 V4 1.70GHz"), TEXT("E5-2630 V3 2.40GHz"), TEXT("E5-2650 V4 2.20GHz"), TEXT("E5-2620 V4 2.10GHz"), NULL };
const int XeonPrices[] = { NULL, 24228, 16880, 20521, 55540, 95987, 34555, NULL };

const TCHAR *Ryzen3Models[] = { TEXT("Select the component"), TEXT("1300X 3.50GHz"), TEXT("1200 3.10GHz"), NULL };
const int Ryzen3Prices[] = { NULL, 10370, 8199, NULL };

const TCHAR *Ryzen5Models[] = { TEXT("Select the component"), TEXT("1500X 3.60GHz"), TEXT("1600 3.20GHz"), TEXT("1400 3.20GHz"), TEXT("1600X 4.00GHz"), NULL };
const int Ryzen5Prices[] = { NULL, 14430, 17025, 12650, 19360, NULL };

const TCHAR *Ryzen7Models[] = { TEXT("Select the component"), TEXT("1700 3.70GHz"), TEXT("1700X 3.80GHz"), TEXT("1800X 4.00GHz"), NULL };
const int Ryzen7Prices[] = { NULL, 25055, 29000, 39474, NULL };

const TCHAR *RyzenThreadripperModels[] = { TEXT("Select the component"), TEXT("TR 1900X 3.80GHz"), TEXT("TR 1920X 4.00GHz"), TEXT("TR 1950X 4.00GHz"), NULL };
const int RyzenThreadripperPrices[] = { NULL, 44800, 65487, 82008, NULL };

const TCHAR *ASeriesAPUModels[] = { TEXT("Select the component"), TEXT("A6-9500 Dual Core 3.50Ghz"), TEXT("A4-4020 3.20Ghz"), NULL };
const int APUPrices[] = { NULL, 5025, 2441, NULL };

const TCHAR *FXSeriesModels[] = { TEXT("Select the component"), TEXT("FX-6300 3.50GHz"), TEXT("FX-4300 3.80GHz"), NULL };
const int FXPrices[] = { NULL, 7925, 6799, NULL };

const TCHAR *MotherboardVendor[] = { TEXT("Select the component"), TEXT("Asus"), TEXT("Gigabyte"), NULL };

const TCHAR *AsusMotherboards[] = { TEXT("Select the component"), TEXT("B250"), TEXT("EX-H110M-V"), TEXT("Intel Z370 Maximus-X"), TEXT("Intel PRIME Z370-A"), TEXT("STRIX-Z370-E"), TEXT("STRIX-Z370-F"), TEXT("TUF-Z370-PLUS"), TEXT("TUF-Z370-PRO"), NULL };
const int AsusMotherboardsPrices[] = { NULL, 14999, 4800, 24827, 16375, 19195, 17121, 14264, 15310, NULL };

const TCHAR *GigabyteMotherboard[] = { TEXT("Select the component"), TEXT("GA-H110-D3A"), TEXT("Z370 Aorus Gaming 3"), TEXT("Z370 Aorus Gaming 5"), TEXT("Z370 Aorus Gaming 7"), TEXT("Z370 Aorus Gaming Wifi"), TEXT("Z370 Aorus Ultra Gaming"), TEXT("Z370 HD3P"), TEXT("Z370M D3H Ultra Durable"), NULL };
const int GigabyteMotherboardPrices[] = { NULL, 7899, 14871, 18280, 22478, 16022, 14677, 12079, 11258, NULL };

const TCHAR *RAMVendor[] = { TEXT("Select the component"), TEXT("Corsair"), TEXT("G Skill"), TEXT("Kingston"), NULL };
const TCHAR *RAMType[] = { TEXT("Select the component"), TEXT("DDR3"), TEXT("DDR4"), NULL };
const TCHAR *RAMCapacity[] = { TEXT("Select the component"), TEXT("4 GB"), TEXT("8 GB"), TEXT("16 GB"), TEXT("32 GB"), NULL };

const int Corsair4GBDDR3 = 3500;
const int Corsair8GBDDR3 = 5500;
const int Corsair16GBDDR3 = 10000;
const int Corsair32GBDDR3 = 18000;

const int Corsair4GBDDR4 = 4500;
const int Corsair8GBDDR4 = 10000;
const int Corsair16GBDDR4 = 16000;
const int Corsair32GBDDR4 = 33000;

const int GSkill4GBDDR3 = 3500;
const int GSkill8GBDDR3 = 9500;
const int GSkill16GBDDR3 = 18000;
const int GSkill32GBDDR3 = 32000;

const int GSkill4GBDDR4 = 4000;
const int GSkill8GBDDR4 = 10000;
const int GSkill16GBDDR4 = 20000;
const int GSkill32GBDDR4 = 35000;

const int Kingston4GBDDR3 = 3000;
const int Kingston8GBDDR3 = 5000;
const int Kingston16GBDDR3 = 9500;
const int Kingston32GBDDR3 = 17000;

const int Kingston4GBDDR4 = 4000;
const int Kingston8GBDDR4 = 9000;
const int Kingston16GBDDR4 = 17000;
const int Kingston32GBDDR4 = 28000;

const TCHAR *GPUVendor[] = { TEXT("Select the component"), TEXT("Nvidia GeForce"), TEXT("AMD Radeon"), NULL };
const TCHAR *NvidiaSeries[] = { TEXT("Select the component"), TEXT("GeForce 700"), TEXT("GeForce 900"), TEXT("GeForce 1000"), NULL };
const TCHAR *AMDSeries[] = { TEXT("Select the component"), TEXT("RX 400"), TEXT("RX 500"), TEXT("RX Vega"), NULL };

const TCHAR *GeForce700Models[] = { TEXT("Select the component"), TEXT("MSI GT 710 2GB DDR5"), TEXT("Zotac GTX 750Ti 2GB DDR5"), TEXT("EVGA GT 730 2GB DDR3"), NULL };
const int GeForce700Prices[] = { NULL, 2979, 10000, 5500, NULL };

const TCHAR *GeForce900Models[] = { TEXT("Select the component"), TEXT("Gigabyte GTX 950 2GB DDR5"), NULL };
const int GeForce900Prices[] = { NULL, 9500, NULL };

const TCHAR *GeForce1000Models[] = { TEXT("Select the component"), TEXT("MSI GT 1030 2GB DDR3"), TEXT("MSI GTX 1050 2GB DDR5"), TEXT("MSI GTX 1050Ti 2GB DDR5"), TEXT("GALAX GTX 1050Ti"), TEXT("MSI GTX 1060 3GB DDR5"), TEXT("MSI GTX 1060 6GB DDR5"), TEXT("ASUS GTX 1070Ti 8GB DDR5"), TEXT("GALAX GTX 1070Ti 8GB DDR5"), TEXT("Gigabyte GTX 1080Ti 11GB DDR5"), TEXT("MSI GTX 1080Ti 11GB DDR5"), NULL };
const int GeForce1000Prices[] = { NULL, 5883, 9388, 11266, 12031, 18025, 22907, 48493, 42559, 71299, 61335, NULL };

const TCHAR *RX400Models[] = { TEXT("Select the component"), TEXT("Sapphire Radeon RX460 4GB"), NULL };
const int RX400Prices[] = { NULL, 35000,  NULL };

const TCHAR *RX500Models[] = { TEXT("Select the component"), TEXT("Sapphire Radeon RX550"), TEXT("MSI Radeon RX560 4GB"), TEXT("Gigabyte Radeon RX570"), TEXT("MSI Radeon RX580 8GB"), NULL };
const int RX500Prices[] = { NULL, 7550, 10515, 24399, 31294, NULL };

const TCHAR *RXVegaModels[] = { TEXT("Select the component"), TEXT("MSI RXVega 56 8GB"), TEXT("Sapphire RXVega 56 8GB"), TEXT("Sapphire RXVega 64 8GB"), NULL };
const int RXVegaPrices[] = { NULL, 46299, 41371, 51449, NULL };

const TCHAR *HDDVendor[] = { TEXT("Select the component"), TEXT("Western Digital"), TEXT("Seagate"), NULL };
const TCHAR *HDDCapacity[] = { TEXT("Select the component"), TEXT("1TB"), TEXT("2TB"), TEXT("4TB"), TEXT("8TB"), NULL };

const TCHAR *WD1TB[] = { TEXT("Select the component"), NULL };
const int WD1TBPrice[] = { NULL, 3199, NULL };
const TCHAR *WD2TB[] = { TEXT("Select the component"), NULL };
const int WD2TBPrice[] = { NULL, 6800, NULL };
const TCHAR *WD4TB[] = { TEXT("Select the component"), NULL };
const int WD4TBPrice[] = { NULL, 16273, NULL };
const TCHAR *WD8TB[] = { TEXT("Select the component"), NULL };
const int WD8TBPrice[] = { NULL, 31294, NULL };

const TCHAR *Seagate1TB[] = { TEXT("Select the component"), NULL };
const int Seagate1TBPrice[] = { NULL, 4000, NULL };
const TCHAR *Seagate2TB[] = { TEXT("Select the component"), NULL };
const int Seagate2TBPrice[] = { NULL, 6384, NULL };
const TCHAR *Seagate4TB[] = { TEXT("Select the component"), NULL };
const int Seagate4TBPrice[] = { NULL, 9250, NULL };
const TCHAR *Seagate8TB[] = { TEXT("Select the component"), NULL };
const int Seagate8TBPrice[] = { NULL, 26287, NULL };
//const TCHAR *HDDSpeed[] = { TEXT("Select HDD Speed"), TEXT("5400 RPM"), TEXT("7200 RPM"), NULL };

const TCHAR *MonitorVendor[] = { TEXT("Select the component"), TEXT("ASUS"), TEXT("SAMSUNG"), NULL };
const TCHAR *MonitorScreenSize[] = { TEXT("Select the component"), TEXT("21.5\""), TEXT("24\""), TEXT("27\""), TEXT("31.5\""), NULL };
const TCHAR *MonitorResolution[] = { TEXT("Select the component"), TEXT("1080p"), NULL };

const int ASUS1080_21_5 = 12220;
const int ASUS1080_24 = 53634;
const int ASUS1080_27 = 21589;
const int ASUS1080_31_5 = 41414;

const int SAMSUNG1080_21_5 = 12220;
const int SAMSUNG1080_24 = 53634;
const int SAMSUNG1080_27 = 21589;
const int SAMSUNG1080_31_5 = 41414;

const TCHAR *SMPSVendor[] = { TEXT("Select the component"), TEXT("Cooler Master"), TEXT("Corsair"), NULL };
const TCHAR *SMPSCapacity[] = { TEXT("Select the component"), TEXT("650W"), TEXT("750W"), TEXT("850W"), TEXT("1000W"), TEXT("1200W"), NULL };

const int CM650 = 5749;
const int CM750 = 7649;
const int CM850 = 12365;
const int CM1000 = 15900;
const int CM1200 = 18000;

const int Corsair650 = 9152;
const int Corsair750 = 11138;
const int Corsair850 = 13649;
const int Corsair1000 = 16999;
const int Corsair1200 = 19000;

const TCHAR *CabinetVendor[] = { TEXT("Select the component"), TEXT("Corsair"), TEXT("Cooler Master"), NULL };
const TCHAR *CMCabinets[] = { TEXT("Select the component"), TEXT("Cooler Master CMP 250 Mid Tower"), TEXT("Masterbox 5 ATX Mid Tower"), TEXT("Mastercase Pro 6"), NULL };
const int CMCabinetCost[] = { NULL, 2253, 6509, 10953, NULL };
const TCHAR *CorsairCabinet[] = { TEXT("Select the component"),TEXT("Carbide Series 88R"), TEXT("Carbide Series 270R"), TEXT("Obsidian Series 650D"), NULL };
const int CorsairCabinetCost[] = { NULL, 3436, 4999, 15892, NULL };

const TCHAR *DVDSpeed[] = { TEXT("Select the component"), TEXT("LG BluRay DVD Drive 16x"), TEXT("ASUS BluRay DVD Drive 16x"), NULL };
const int DVDPrice[] = { NULL, 3500, 3550, NULL };

const TCHAR *Keyboard[] = { TEXT("Select the component"), TEXT("HyperX Alloy Elite Cherry MX Red Gaming Keyboard"), TEXT("HYPERX ALLOY FPS CHERRY MX BLUE/RED Mechanical"), TEXT("Corsair Gaming K70 RGB RAPIDIFRE Backlit Mechanical"), TEXT("Corsair K55 RGB Gaming Keyboard"), TEXT("Cooler master Devastator 3"), TEXT("Cooler Master MasterKeys Pro L Mechanical Keyboard"), NULL };
const int KeyboardCost[] = { NULL, 9999, 7700, 11516, 4500, 2999, 14533, NULL };

const TCHAR *Mouse[] = { TEXT("Select the component"), TEXT("Corsair Gaming HARPOON"), TEXT("HyperX Pulsefire"), TEXT("Razer DeathAdder"), TEXT("Razer DeathAdder Elite"), NULL };
const int MouseCost[] = { NULL, 1799, 3200, 3755, 4819, NULL };


struct Processor
{
	const TCHAR *CPUVendor;
	const TCHAR *IntelSubType;
	const TCHAR *AMDSubType;
};

struct Motherboard
{

};

struct Memory
{

};

struct GraphicsCard
{

};

struct HardDisk
{

};

struct Monitor
{

};

struct Cabinet
{

};

struct Keyboard
{

};

struct DVDDrive
{

};

struct Mouse
{

};
