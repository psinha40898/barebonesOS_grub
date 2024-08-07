<h1>A very basic x86 operating system</h1>
<ul>
<li>GRUB bootloader loads custom kernel</li>
<li>Keyboard and Screen drivers defined to interact with appropriate Framebuffer memory locations</li>
<li>Loader.s defined in NASM x86 assembly to create Kernel stack and load C Kernel</li>
<li>GDT and IDT Defined in C to facilitate x86 memory management</li>
<li>Compiled with GCC and NASM</li>
<li>Runs on x86 Qemu or Bochs emulators</li>
</ul>


<h2>How to Run</h2>
<p>To build the project and create the ISO image, follow these steps:</p>
<ol>
  <li>Run <code>make</code> to compile the kernel and build the ISO image:</li>
  <pre><code>make oshome.iso</code></pre>
  <li>Once the build process is complete, you can run the ISO image using QEMU:</li>
  <pre><code>qemu-system-x86_64 -cdrom os.iso -boot d -monitor stdio</code></pre>
</ol>

<h2>References</h2>
<a href = "https://littleosbook.github.io/">Little OS Book</a>

