# freeview_wasm

To build:

1. Download and install emscripten sdk
   https://emscripten.org/docs/getting_started/downloads.html

2. Download and install Qt 6.6.3 for WebAssembly (single_thread)
   https://www.qt.io/download-qt-installer-oss?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4

3. Download and build VTK 9.3.1 using emscripten
   https://vtk.org/download/

   Buld instruction:
   https://docs.vtk.org/en/latest/advanced/build_wasm_emscripten.html

4. Build freeview_wasm
   Open Qt Creater IDE, load the project by selecting CMakeFiles.txt.
