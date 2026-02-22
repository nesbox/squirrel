.. _repl:

#################################
  Try Squirrel online
#################################

.. raw:: html

  <style>
    .content-wrapper
    {
      display: flex;
      margin-bottom: 12px;
      gap: 12px;
    }

    #btn-run, #btn-copy-link
    {
      margin-left: 0;
    }

    #btn-copy-link
    {
      margin-left: auto;
    }

    #btn-run, #btn-copy-link
    {
      padding: 6px 12px;
      border-radius: 6px;
      background-color: #eee;
      border: 1px solid #ddd;
      cursor: pointer;
    }

    #btn-run:hover, #btn-copy-link:hover
    {
      background-color: #ddd;
    }

    #script
    {
      min-height: 450px;
      border: 1px solid #ddd;
      border-radius: 6px;
    }

    #output
    {
      min-height: 200px;
      font-family: consolas;
      font-size: 14px;
      resize: none;
      cursor: default;
      border: 1px solid #ddd;
      border-radius: 6px;
      padding: 6px;
    }
  </style>

  <script src="../_static/sq_wasm.js"></script>
  <script src="../_static/monaco-editor/min/vs/loader.js"></script>

  <script>
    require.config({ paths: { 'vs': '../_static/monaco-editor/min/vs' }});

    let codeEditor;

    require(["vs/editor/editor.main"], function ()
    {
      monaco.languages.register({ id: "squirrel" });

      monaco.languages.setMonarchTokensProvider("squirrel",
      {
        tokenizer: {
          root: [
            [/\bbase\b/, 'keyword'],
            [/\bbreak\b/, 'keyword'],
            [/\bcase\b/, 'keyword'],
            [/\bcatch\b/, 'keyword'],
            [/\bclass\b/, 'keyword'],
            [/\bclone\b/, 'keyword'],
            [/\bcontinue\b/, 'keyword'],
            [/\bconst\b/, 'keyword'],
            [/\bdefault\b/, 'keyword'],
            [/\bdelete\b/, 'keyword'],
            [/\belse\b/, 'keyword'],
            [/\benum\b/, 'keyword'],
            [/\bextends\b/, 'keyword'],
            [/\bfor\b/, 'keyword'],
            [/\bforeach\b/, 'keyword'],
            [/\bfunction\b/, 'keyword'],
            [/\bif\b/, 'keyword'],
            [/\bin\b/, 'keyword'],
            [/\blocal\b/, 'keyword'],
            [/\bnull\b/, 'keyword'],
            [/\bresume\b/, 'keyword'],
            [/\breturn\b/, 'keyword'],
            [/\bswitch\b/, 'keyword'],
            [/\bthis\b/, 'keyword'],
            [/\bthrow\b/, 'keyword'],
            [/\btry\b/, 'keyword'],
            [/\btypeof\b/, 'keyword'],
            [/\bwhile\b/, 'keyword'],
            [/\byield\b/, 'keyword'],
            [/\bconstructor\b/, 'keyword'],
            [/\bdestructor\b/, 'keyword'],
            [/\binstanceof\b/, 'keyword'],
            [/\btrue\b/, 'keyword'],
            [/\bfalse\b/, 'keyword'],
            [/\bstatic\b/, 'keyword'],
            [/\b__LINE__\b/, 'keyword'],
            [/\b__FILE__\b/, 'keyword'],
            [/\brawcall\b/, 'keyword'],

			      [/\b0x[0-9A-Fa-f]+\b/, 'number.hexadecimal'], 
			      [/\b0[0-7]+\b/, 'number.octal'],
			      [/\d+/, 'number'],
			      [/'.'/, 'number'],
			      [/\b\d+\.\d+([eE][+-]?\d+)?\b/, 'number.float'],
			      [/\b\d+\.[eE][+-]?\d+\b/, 'number.float'],

			      [/"([^"\\]|\\[abfnrtv"\\]|\\x[0-9A-Fa-f]{1,2})*"/, 'string'],
            [/'([^'\\]|\\[abfnrtv'\\]|\\x[0-9A-Fa-f]{1,2})*'/, 'string.character'],

            [/"([^"\\]|\\[n\"\\]|\\x[0-9A-Fa-f]{1,2}|\\[abfnrtv])*"/, 'string'],
            [/"(\\[abfnrtv])/, 'string.escape'],
            [/"(\\x[0-9A-Fa-f]{1,2})/, 'string.escape'],

			      [/@"/, { token: 'string.verbatim', next: '@verbatimString' }],
            [/`/, { token: 'string.template', next: '@templateString' }],

			      [/\/\*/, { token: 'comment', next: '@comment' }],
            [/\/\/.*/, 'comment'],
            [/\#.*/, 'comment'],

            [/[a-zA-Z_$][\w$]*/, 'identifier'],
            [/[{}[\]()]/, '@brackets'],
          ],

		    verbatimString: [
			    [/[^"]+/, 'string.verbatim'],
			    [/""/, 'string.verbatim'],
			    [/"/, { token: 'string.verbatim', next: '@pop' }]
		    ],

        templateString: [
            [/\$\{/, { token: 'delimiter.bracket', next: '@templateExpression' }],
            [/\\[`$]/, 'string.escape'],
            [/`/, { token: 'string.template', next: '@pop' }],
            [/[^\\`$]+/, 'string.template'],
            [/\\./, 'string.escape'],
        ],

        templateExpression: [
          [/\}/, { token: 'delimiter.bracket', next: '@pop' }],
          [/\b0x[0-9A-Fa-f]+\b/, 'number.hexadecimal'],
          [/\b0[0-7]+\b/, 'number.octal'],
          [/\d+/, 'number'],
          [/\b\d+\.\d+([eE][+-]?\d+)?\b/, 'number.float'],
          [/"([^"\\]|\\.)*"/, 'string'],
          [/'([^'\\]|\\.)*'/, 'string'],
          [/[a-zA-Z_$][\w$]*/, 'identifier'],
          [/[-+*/%=!<>|&]+/, 'operator'],
          [/[()[\]]/, '@brackets'],
          [/\s+/, 'white'],
        ],

		    comment: [
			    [/[^\*]+/, 'comment'],
			    [/(\*[^\/])/, 'comment'],
			    [/(\*\/)/, { token: 'comment', next: '@pop' }]
		    ]
      },
    });

      monaco.languages.setLanguageConfiguration("squirrel",
      {
        comments: {
          lineComment: ['//', '#'],
          blockComment: ['/*', '*/']
        },
        brackets: [
          ['{', '}'],
          ['[', ']'],
          ['(', ')']
        ],
        autoClosingPairs: [
          { open: '{', close: '}' },
          { open: '[', close: ']' },
          { open: '(', close: ')' },
          { open: '"', close: '"' }
        ]
      });

      codeEditor = monaco.editor.create(document.getElementById("script"),
      {
        value: getCodeFromUrl() ?? `print("Hello from " + _version_)`,
        language: 'squirrel',
        theme: 'vs-light'
      });
    });

    function alloc_cpp_string(text)
    {
      const lengthBytes = lengthBytesUTF8(text) + 1;
      const ptr = Module._sq_malloc(lengthBytes);

      stringToUTF8(text, ptr, lengthBytes);

      return ptr;
    }

    function free_cpp_string(ptr)
    {
      Module._sq_free(ptr);
    }

    function execute_sq()
    {
      const code_cpp_text = alloc_cpp_string(codeEditor.getValue());

      Module._sq_execute(code_cpp_text);
      free_cpp_string(code_cpp_text);
    }

    function getCodeFromUrl()
    {
      const urlParams = new URLSearchParams(window.location.search);
      const code = urlParams.get("code");

      if (code)
      {
        return window.atob(code);
      }

      return null;
    }

    function copy_data_url()
    {
      const code = codeEditor.getValue();
      const encodedCode = window.btoa(code);
      const url = new URL(window.location);

      url.searchParams.set("code", encodedCode);
      navigator.clipboard.writeText(url.toString());
    }

    document.addEventListener("keyup", function(e)
    {
      if (e.key === "Enter" && e.altKey)
      {
        execute_sq()
        e.preventDefault()
      }
    })
  </script>

    <div class="content-wrapper">
      Source code

      <button id="btn-copy-link" onclick="copy_data_url()">Copy link</button>
      <button id="btn-run" onclick="execute_sq()">Run (Alt + Enter)</button>
    </div>

  <div id="script">
  </div>

  <br/>

  <div class="content-wrapper">
    Result
  </div>

  <textarea id="output" readonly>
  </textarea>

  <br/><br/>