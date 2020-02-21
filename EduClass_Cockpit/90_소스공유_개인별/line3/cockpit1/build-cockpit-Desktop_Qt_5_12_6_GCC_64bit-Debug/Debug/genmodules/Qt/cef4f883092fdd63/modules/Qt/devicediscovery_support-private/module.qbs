import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "DeviceDiscoverySupport"
    Depends { name: "Qt"; submodules: ["core-private"]}

    architectures: ["x86_64"]
    targetPlatform: "linux"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: ["/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5Core.so"]
    dynamicLibsDebug: []
    dynamicLibsRelease: []
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5DeviceDiscoverySupport"
    libNameForLinkerRelease: "Qt5DeviceDiscoverySupport"
    libFilePathDebug: undefined
    libFilePathRelease: "/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5DeviceDiscoverySupport.a"
    pluginTypes: []
    moduleConfig: ["lex","yacc","depend_includepath","testcase_targets","import_qpa_plugin","qt_build_extra","file_copies","qmake_use","qt","warn_on","release","link_prl","incremental","release","linux","unix","posix","gcc","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","avx","avx2","avx512f","avx512bw","avx512cd","avx512dq","avx512er","avx512ifma","avx512pf","avx512vbmi","avx512vl","compile_examples","enable_new_dtags","f16c","force_debug_info","largefile","rdrnd","shani","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","prepare_docs","qt_docs_targets","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","explicitlib","warning_clean","static","internal_module","relative_qt_rpath","git_build","qmake_cache","target_qt","c++11","strict_c++","c++14","c99","c11","hide_symbols","bsymbolic_functions","separate_debug_info","qt_install_headers","need_fwd_pri","qt_install_module","compiler_supports_fpmath","create_libtool","have_target","staticlib","debug_info","thread","moc","resources"]
    cpp.defines: ["QT_DEVICEDISCOVERY_SUPPORT_LIB"]
    cpp.includePaths: ["/home/class/Qt5.12.6/5.12.6/gcc_64/include","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtDeviceDiscoverySupport","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtDeviceDiscoverySupport/5.12.6","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtDeviceDiscoverySupport/5.12.6/QtDeviceDiscoverySupport"]
    cpp.libraryPaths: ["/home/qt/openssl-1.1.1b/lib"]
    isStaticLibrary: true
Group {
        files: [Qt["devicediscovery_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
