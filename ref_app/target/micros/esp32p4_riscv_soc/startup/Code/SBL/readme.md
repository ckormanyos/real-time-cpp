# ESP32-P4 SBL (Secondary Boot Loader)

The SBL (Secondary Boot Loader) is used in combination with the ESP-flash
tool to boot the multi-core device.

The SBL has been adopted directly from the original work in
[Chalandi/Baremetal_esp32p4_nosdk](https://github.com/Chalandi/Baremetal_esp32p4_nosdk).
In that work, the SBL code and build system can be found in the
[SBL](https://github.com/Chalandi/Baremetal_esp32p4_nosdk/tree/master/Code/SBL) directory.

The original _chalandi_ project has been used locally to build the SBL
for target `esp32p4_riscv_soc` in the `ref_app`.
The SBL-Output from that build has been archived and can be found
in the [Output](./Output) directory.
