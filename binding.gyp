{
  "targets": [
    {
      "target_name": "<(module_name)",
      "product_dir": "<(module_path)",
      "type": "none",
      "actions": [
        {
          "action_name": "ncmake",
          "inputs": [""],
          "outputs": [""],
          "conditions": [
            [ "OS=='linux'",
                {"action": ["npm", "run", "cmake-rebuild", "-DNAPI_VERSION=<(napi_build_version)"]}
            ]
          ]
        }
      ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        },
        {
          "files": [ ],
          "conditions": [
            [ "OS=='linux'",
                { "files+": [
                    "libtorch/lib/libc10.so",
                    "libtorch/lib/libcaffe2_detectron_ops.so",
                    "libtorch/lib/libcaffe2_module_test_dynamic.so",
                    "libtorch/lib/libfbjni.so",
                    "libtorch/lib/libgomp-7c85b1e2.so.1",
                    "libtorch/lib/libpytorch_jni.so",
                    "libtorch/lib/libtorch.so"
                  ]
                }
            ]
          ],
          "destination": "<(module_path)"
        }
      ]
    }
  ]
}
