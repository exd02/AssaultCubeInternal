<h2>Internal Assault Cube (AC) Cheat.</h2>

![image](https://github.com/exd02/AssaultCubeInternal/assets/62575526/cb20aa64-745d-496e-a953-c939bc35dcce)


<section>
    <h2>Hooking</h2>
    <p>This cheat runs every tick of the game by doing a Trampoline Hook on the function <code>wglSwapBuffers</code> from the <code>opengl32.dll</code>. The SDL2 (Engine used by AC) uses the function <code>wglSwapBuffers</code>. This function is called at the end of each frame rendering process.</p>
    <h4>Materials that helped me to understand the concepts of Hooking:</h4>
    <ul>
        <li><a href="http://jbremer.org/x86-api-hooking-demystified/">jbremer general explaining of hooking</a></li>
        <li><a href="https://youtu.be/jTl3MFVKSUM">GH - Solaire Basic Hook Tutorial</a></li>
        <li><a href="https://youtu.be/HLh_9qOkzy0">GH - Rake Trampoline Hook Tutorial</a></li>
    </ul>
</section>

<section>
    <h2>Extra-Sensory Perception (ESP)</h2>
    <p>Currently studying and putting the materials here.</p>
    <ol>
        <li>
            <h4>Understand OpenGL:</h4>
            <ul>
                <li><a href="https://youtu.be/W3gAzLwfIP0?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2">The Cherno OpenGL YouTube Playlist</a></li>
                <li><a href="https://learnopengl.com/Getting-started/OpenGL">Website explaining everything about OpenGL</a></li>
            </ul>
        </li>
        <li>
            <h4>How World to Screen works:</h4>
            <ul>
                <li><a href="https://www.youtube.com/watch?v=eoXn6nwV694">How Do Computers Display 3D on a 2D Screen?</a></li>
                <li><a href="https://www.codereversing.com/archives/530">Website explaining World to Screen with code</a></li>
            </ul>
        </li>
        <li>
            <h4>ViewMatrix:</h4>
            <ul>
                <li><a href="https://siware.dev/009-transformation-notes/">Website explaining ViewMatrix Math</a></li>
                <li><a href="https://youtu.be/-WL1Gpe9VRo">Finding your ViewMatrix in AssaultCube</a></li>
                <li><a href="https://youtu.be/crT9zGviqVs">Finding your ViewMatrix in CS:GO</a></li>
            </ul>
        </li>
        <li>
            <h4>Drawing inside the Game:</h4>
            <ul>
                <li><a href="https://youtu.be/dEgva5-OsSY">Drawing inside AC (part 1)</a></li>
                <li><a href="https://youtu.be/6JV0dmLWMNs">Drawing inside AC (part 2)</a></li>
            </ul>
        </li>
    </ol>
    <p>Only for educational purposes.</p>
</section>
