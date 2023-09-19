{
    "targets": [
        {
            "target_name": "ksu",
            "include_dirs": [
                "<!(sh -c \"echo \$PWD/include\")",
                "<!(node -p \"require('node-addon-api').include_dir\")",
            ],
            "sources": [
                "src/ksu.cpp",
                "src/KernelSU.cpp",
            ],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
        },
    ]
}
