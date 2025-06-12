<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
</head>
<body>
<p align="center">
  <img src="imgs/minipink.png" width="400px"" />
</p>


  <h1>🌸 Minishell - As Beautiful As a Shell</h1>

  <p>This project is part of the 42 School curriculum. Its purpose is to create a simpler Unix shell implemented in C. The shell mimics basic behavior of <code>bash</code> and provides a functional command-line interface.</p>

  <h2>📝 Summary</h2>
  <p>Minishell is a custom implementation of a shell interface, developed to understand the inner workings of processes, file descriptors, and signal handling. It also offers a chance to master memory management and parsing techniques in C.</p>

  <h2>✅ Features</h2>

  <h3>Mandatory Part</h3>
  <ul>
    <li>Custom prompt display</li>
    <li>Command execution using:
      <ul>
        <li>Relative or absolute paths</li>
        <li>PATH environment variable</li>
      </ul>
    </li>
    <li>Environment variable expansion (<code>$VAR</code>, <code>$?</code>)</li>
    <li>Built-in commands:
      <ul>
        <li><code>echo [-n]</code></li>
        <li><code>cd</code></li>
        <li><code>pwd</code></li>
        <li><code>export</code></li>
        <li><code>unset</code></li>
        <li><code>env</code></li>
        <li><code>exit</code></li>
      </ul>
    </li>
    <li>Pipes (<code>|</code>) support</li>
    <li>Redirections:
      <ul>
        <li><code>&lt;</code>, <code>&gt;</code>, <code>&gt;&gt;</code>, <code>&lt;&lt;</code> (heredoc)</li>
      </ul>
    </li>
    <li>Proper signal handling:
      <ul>
        <li><code>Ctrl+C</code>, <code>Ctrl+D</code>, <code>Ctrl+\</code></li>
      </ul>
    </li>
    <li>Quote handling:
      <ul>
        <li><code>'single quotes'</code></li>
        <li><code>"double quotes"</code></li>
      </ul>
    </li>
  </ul>


  <h2>⚙️ Usage</h2>
  <ol>
    <li>Clone the repository:
      <pre><code>git clone https://github.com/your-username/minishell.git
cd minishell</code></pre>
    </li>
    <li>Compile the project:
      <pre><code>make</code></pre>
    </li>
    <li>Run the shell:
      <pre><code>./minishell</code></pre>
    </li>
  </ol>


  <h2>🧠 Learnings</h2>
  <p>Through this project, we learned about:</p>
  <ul>
    <li>Process forking and piping</li>
    <li>File descriptor duplication</li>
    <li>Signal and memory management</li>
    <li>Writing parsers and tokenizers</li>
    <li>Recreating <code>bash</code>-like behavior in C</li>
  </ul>

  <h2>👨‍💻 Authors</h2>
  <p>This project was made by <strong>Jard Noan <strong> and <strong>Naziha Aankour </strong>.</p>

</body>
</html>
