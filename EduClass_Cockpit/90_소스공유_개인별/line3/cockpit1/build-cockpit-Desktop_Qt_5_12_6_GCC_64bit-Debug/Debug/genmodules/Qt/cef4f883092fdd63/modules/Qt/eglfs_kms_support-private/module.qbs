import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "EglFsKmsSupport"
    Depends { name: "Qt"; submodules: ["core","gui"]}

    architectures: ["x86_64"]
    targetPlatform: "linux"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: ["/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5EglFSDeviceIntegration.so","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5EventDispatcherSupport.a","gthread-2.0","glib-2.0","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5ServiceSupport.a","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5ThemeSupport.a","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5FontDatabaseSupport.a","fontconfig","freetype","z","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5FbSupport.a","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5EglSupport.a","EGL","Xext","X11","m","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5InputSupport.a","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5PlatformCompositorSupport.a","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5KmsSupport.a","dl","GL","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5Gui.so","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5DeviceDiscoverySupport.a","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5EdidSupport.a","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5DBus.so","drm","dl"]
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5EglFsKmsSupport"
    libNameForLinkerRelease: "Qt5EglFsKmsSupport"
    libFilePathDebug: undefined
    libFilePathRelease: "/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5EglFsKmsSupport.so.5.12.6"
    pluginTypes: []
    moduleConfig: ["lex","yacc","depend_includepath","testcase_targets","import_plugins","import_qpa_plugin","qt_build_extra","file_copies","qmake_use","qt","warn_on","release","link_prl","incremental","shared","release","linux","unix","posix","gcc","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","avx","avx2","avx512f","avx512bw","avx512cd","avx512dq","avx512er","avx512ifma","avx512pf","avx512vbmi","avx512vl","compile_examples","enable_new_dtags","f16c","force_debug_info","largefile","precompile_header","rdrnd","shani","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","prepare_docs","qt_docs_targets","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","explicitlib","warning_clean","no_module_headers","internal_module","relative_qt_rpath","git_build","qmake_cache","target_qt","c++11","strict_c++","c++14","c99","c11","hide_symbols","bsymbolic_functions","separate_debug_info","need_fwd_pri","qt_install_module","compiler_supports_fpmath","create_libtool","egl","have_target","dll","debug_info","thread","opengl","dbusadaptors","dbusinterfaces","moc","resources"]
    cpp.defines: ["QT_EGLFS_KMS_SUPPORT_LIB"]
    cpp.includePaths: []
    cpp.libraryPaths: ["/home/qt/openssl-1.1.1b/lib"]
    Group {
        files: [Qt["eglfs_kms_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary"]
    }
}
