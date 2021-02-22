

/*

#include <Windows.h>

#include "main.hpp"
#define ORDER_SHIT_FUCK
#include <Psapi.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <typeinfo>

static void Initialize();
static void SetupConsole();

static HMODULE GetModuleFromName(const std::string& name);
static std::uintptr_t FindPattern(const char* pattern, const char* hexdump,
                                  std::size_t len, HMODULE base_address);
static uint8_t HexToInt(const char* str);

static void GetSendTableCRC32();

static HMODULE current_module;
static HANDLE current_process;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      SetupConsole();
      Initialize();
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}

static void SetupConsole() {
  AllocConsole();

  freopen("CONIN$", "r", stdin);
  freopen("CONOUT$", "w", stdout);
  freopen("CONOUT$", "w", stderr);
  printf("RANDOM SHIT\n");
}

static HMODULE GetModuleFromName(const std::string& name) {
  HMODULE modules[1024];
  DWORD module_count = 0;
  EnumProcessModules(current_process, modules, sizeof(modules), &module_count);
  module_count /= sizeof(HMODULE);
  if (module_count > 0) {
    char module_name[0x80];
    for (DWORD i = 0; i < module_count; i++) {
      DWORD module_name_size =
          GetModuleBaseName(current_process, modules[i], module_name, 0x80);
      std::string module_name_str(module_name, module_name_size);
      if (module_name_str.find(name) != name.npos) {
        return modules[i];
      }
    }
  }

  return nullptr;
}

static std::uintptr_t FindPattern(const char* pattern, const char* hexdump,
                                  std::size_t len, HMODULE base_address) {
  std::uintptr_t image_base = 0;
  std::size_t image_size = 0;
  {
    MODULEINFO info{};
    auto lol = GetModuleInformation(current_process, base_address, &info,
                                    sizeof(info));
    image_base = reinterpret_cast<std::uintptr_t>(info.lpBaseOfDll);
    image_size = info.SizeOfImage;
  }

  for (std::size_t off = 0; off < (image_size - len); off++) {
    for (std::size_t i = 0; i < len; i++) {
      std::uint8_t current_byte =
                       reinterpret_cast<std::uint8_t*>(image_base + off + i)[0],
                   check_byte = HexToInt(hexdump + 2 * i);

      if (pattern[i] == '?') continue;
      if (check_byte != current_byte) break;

      if (i == len - 1) {
        return image_base + off;
      }
    }
  }
  return 0;
}

static void GetSendTableCRC32() {
  const auto engine_module = GetModuleFromName("engine.dll");
  if (engine_module != nullptr) {
    printf("found engine module!\n");

    std::uintptr_t addr = FindPattern(
        "xxxxxxxx????xx", "558BEC83EC0C833DCCCCCCCC0053", 14ull, engine_module);
    if (addr != 0) {
      printf("found addr %p\n", &addr);

      uint8_t* addr1 = reinterpret_cast<uint8_t*>(addr) + 205;
      uint32_t addr2 = *reinterpret_cast<uint32_t*>(addr);
      addr2 = *reinterpret_cast<uint32_t*>(addr);

      std::cout << "sendtable crc32 " << addr2 << std::endl;
    }
  }
}

static void Initialize() {
  current_module = GetModuleHandle(nullptr);
  current_process = GetCurrentProcess();

  //   GetSendTableCRC32();
}

static uint8_t HexToInt(const char* str) {
  const auto internal1 = [](const char ch) -> uint8_t {
    if (ch >= '0' && ch <= '9') {
      return static_cast<uint8_t>(ch - '0');
    } else {
      if (ch >= 'A' && ch <= 'F') {
        return static_cast<uint8_t>(ch - 'A' + 10);
      } else if (ch >= 'a' && ch <= 'f') {
        return static_cast<uint8_t>(ch - 'a' + 10);
      } else {
        return 0;
      }
    }
  };

  return (internal1(*str) << 4) | internal1(*(str + 1));
}


*/
