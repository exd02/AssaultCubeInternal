<h2>Internal Assault Cube (AC) Cheat.</h2>

![image](https://github.com/exd02/AssaultCubeInternal/assets/62575526/f9541a70-1cfc-42da-ab15-485c9d67c3f8)

<p>If you don't understand some concept like "What is the use of normalizing a Vector" just ask ChatGPT, he will help you a lot in your journey!</p>
<p>I've selected what I consider the best materials to learn each concept and put them here. I hope that they can help u like they helped me, GL!</p>

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
    <p>Materials that helped me to create an ESP.</p>
    <ol>
        <li>
            <h4>Understand OpenGL:</h4>
            <ul>
                <li><a href="https://youtu.be/W3gAzLwfIP0?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2">The Cherno OpenGL YouTube Playlist</a> (you should watch the five first videos at least)</li>
                <li><a href="https://learnopengl.com/Getting-started/OpenGL">Website explaining everything about OpenGL</a></li>
            </ul>
        </li>
        <li>
            <h4>How World to Screen works:</h4>
            <ul>
                <li><a href="https://www.youtube.com/watch?v=eoXn6nwV694">How Do Computers Display 3D on a 2D Screen?</a></li>
                <li><a href="https://www.codereversing.com/archives/530">Website explaining World to Screen with with code</a></li>
            </ul>
        </li>
        <li>
            <h4>ViewMatrix:</h4>
            <ul>
                <li><a href="https://siware.dev/009-transformation-notes/">Website explaining ViewMatrix Math</a></li>
                <li><a href="https://youtu.be/-WL1Gpe9VRo">Finding your ViewMatrix in AssaultCube (GH - Rake)</a></li>
                <li><a href="https://youtu.be/crT9zGviqVs">Finding your ViewMatrix in CS:GO (GH - Rake)</a></li>
            </ul>
        </li>
        <li>
            <h4>EntityList:</h4>
            <ul>
                <li><a href="https://youtu.be/TCu0qSivXUc">Finding EntityList in Assault Cube (GH - Rake)</a></li>
                <li><a href="https://youtu.be/-wYVIJWhPDM">Finding EntityList in Assault Cube (Green Eyes)</a></li>
                <li><a href="https://youtu.be/aYN7IjGubuY">Finding EntityList in Skyrim (GH - Icew0lf)</a></li>
                <li><a href="https://youtu.be/oXlOboQURy0">Finding EntityList in CS:GO (GH - Rake)</a></li> *(interesting to see, it's a linked list)
            </ul>
        </li>
        <li>
            <h4>ESP with OpenGL:</h4>
            <ul>
                <li><a href="https://youtu.be/dEgva5-OsSY">Drawing inside AC (GH - Rake 1/3)</a></li>
                <li><a href="https://youtu.be/6JV0dmLWMNs">Drawing inside AC (GH - Rake 2/3)</a></li>
                <li><a href="https://youtu.be/kGDKQXgxIrY">Making an ESP (GH - Rake 3/3)</a></li>
            </ul>
        </li>
    </ol>
    <p>Only for educational purposes.</p>
</section>

<section>
    <h2>Aimbot</h2>
    <p>Materials that helped me to create an Aimbot.</p>
    <ol>
        <li>
            <h4>Math and code Aimbot:</h4>
            <ul>
                <li><a href="https://youtu.be/sDd8aBCCBbA">CSGO Aimbot Tutorial & CalcAngle Explained (GH - BDKPlayer)</a></li
                <li><a href="https://youtu.be/k8zx_u22dkk">Math behind calculating the view angles (Swedz)</a></li>
                <li><a href="https://youtu.be/0oSo_khxaBk">Aimbot Trigonometry and code (Green Eyes)</a></li>
            </ul>
        </li>
        <li>
            <h4>Visibility Check:</h4>
            <ul>
                <li><a href="https://youtu.be/ANH0OySHPWQ">Visibility Checks (Green Eyes - 1/2)</a></li>
                <li><a href="https://youtu.be/Mhjw1OdPVX8">Visibility Checks (Green Eyes - 1/2)</a></li>
            </ul>
        </li>
        <li>
            <h4>Coding a better aimbot:</h4>
            <ul>
                <li><a href="https://www.unknowncheats.me/forum/counterstrike-global-offensive/137492-math-behind-hack-1-coding-better-aimbot-stop-using-calcangle.html">Better Aimbot (UnknownCheats - InvokeStatic)</a></li>
            </ul>
        </li>
    </ol>
    <p>Only for educational purposes.</p>
</section>
