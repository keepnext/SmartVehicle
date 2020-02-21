import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "VirtualKeyboard"
    Depends { name: "Qt"; submodules: ["core","gui","qml","quick"]}

    architectures: ["x86_64"]
    targetPlatform: "linux"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: ["xcb","xcb-xfixes","/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5Quick.so"]
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5VirtualKeyboard"
    libNameForLinkerRelease: "Qt5VirtualKeyboard"
    libFilePathDebug: undefined
    libFilePathRelease: "/home/class/Qt5.12.6/5.12.6/gcc_64/lib/libQt5VirtualKeyboard.so.5.12.6"
    pluginTypes: ["virtualkeyboard"]
    moduleConfig: ["lex","yacc","depend_includepath","testcase_targets","import_plugins","import_qpa_plugin","qt_build_extra","file_copies","qmake_use","qt","warn_on","release","link_prl","incremental","shared","release","linux","unix","posix","gcc","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","avx","avx2","avx512f","avx512bw","avx512cd","avx512dq","avx512er","avx512ifma","avx512pf","avx512vbmi","avx512vl","compile_examples","enable_new_dtags","f16c","force_debug_info","largefile","precompile_header","rdrnd","shani","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","prepare_docs","qt_docs_targets","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","explicitlib","qtquickcompiler","link_pkgconfig","disable-hunspell","lang-all","lang-ar_AR","lang-bg_BG","lang-cs_CZ","lang-da_DK","lang-de_DE","lang-el_GR","lang-en_GB","lang-en_US","lang-es_ES","lang-es_MX","lang-et_EE","lang-fa_FA","lang-fi_FI","lang-fr_CA","lang-fr_FR","lang-he_IL","lang-hi_IN","lang-hr_HR","lang-hu_HU","lang-id_ID","lang-it_IT","lang-ja_JP","lang-ko_KR","lang-ms_MY","lang-nb_NO","lang-nl_NL","lang-pl_PL","lang-pt_BR","lang-pt_PT","lang-ro_RO","lang-ru_RU","lang-sk_SK","lang-sl_SI","lang-sq_AL","lang-sr_SP","lang-sv_SE","lang-th_TH","lang-tr_TR","lang-uk_UA","lang-vi_VN","lang-zh_CN","lang-zh_TW","openwnn","hangul","pinyin","tcime","thai","cangjie","zhuyin","relative_qt_rpath","git_build","qmake_cache","target_qt","c++11","strict_c++","c++14","c99","c11","hide_symbols","bsymbolic_functions","separate_debug_info","qt_install_headers","need_fwd_pri","qt_install_module","create_cmake","compiler_supports_fpmath","create_pc","create_libtool","have_target","dll","debug_info","thread","opengl","moc","resources"]
    cpp.defines: ["QT_VIRTUALKEYBOARD_LIB"]
    cpp.includePaths: ["/home/class/Qt5.12.6/5.12.6/gcc_64/include","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtVirtualKeyboard"]
    cpp.libraryPaths: ["/home/qt/openssl-1.1.1b/lib"]
    Group {
        files: [Qt["virtualkeyboard"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary"]
    }
}
