<h1>A very basic x86 operating system</h1>


https://github.com/user-attachments/assets/df95e90e-635f-46bc-b431-99466e14a592



<ul>
<li>GRUB bootloader loads custom kernel</li>
<li>Keyboard and Screen drivers defined to interact with appropriate Framebuffer memory locations</li>
<li>Loader.s defined in NASM x86 assembly to create Kernel stack and load C Kernel</li>
<li>GDT and IDT Defined in C to facilitate x86 memory management</li>
<li>Compiled with GCC and NASM</li>
<li>Runs on x86 Qemu or Bochs emulators</li>
</ul>



<h2>How to Run</h2>
<pre><code>
sudo apt-get update

// Install GCC and related tools
sudo apt-get install gcc g++ nasm binutils

// Install multilib support
sudo apt-get install gcc-multilib g++-multilib

// Install ISO creation tools
sudo apt-get install genisoimage mkisofs

// Install QEMU
sudo apt-get install qemu-system-x86
</code></pre>

<p>To build the project and create the ISO image, follow these steps:</p>
<ol>
  <li>Run <code>make</code> to compile the kernel and build the ISO image:</li>
  <pre><code>make oshome.iso</code></pre>
  <li>Once the build process is complete, you can run the ISO image using QEMU:</li>
  <pre><code>qemu-system-x86_64 -cdrom os.iso -boot d -monitor stdio</code></pre>
</ol>

<h2>References</h2>
<a href = "https://littleosbook.github.io/">Little OS Book</a>

