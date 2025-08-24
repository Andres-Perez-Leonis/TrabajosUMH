
// 48642578Q - Practica 2 Flutter

import 'package:flutter/material.dart';

void main() {

  runApp(MaterialApp(home: MainApp()));
}

class MainApp extends StatefulWidget {
  const MainApp({super.key});

  @override
  _MainAppState createState() => _MainAppState();
}

final TextEditingController emailController = TextEditingController();
const String dirImg = 'assets/flutter.jpg';
const String texto = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In lacinia risus sed leo dapibus, a consequat elit mollis. Etiam mattis tellus rhoncus lorem pharetra, sit amet commodo erat convallis. Maecenas porta eget odio aliquam placerat. Morbi sem elit, placerat at dui in, vehicula ultricies felis. Aenean euismod ligula efficitur turpis pharetra vulputate. Nulla facilisi. Fusce bibendum turpis sapien, vitae gravida odio imperdiet tristique. Integer et elit egestas, luctus justo a, sagittis dolor. Integer eu porttitor magna, ut hendrerit leo. Cras commodo turpis a pharetra commodo. Duis aliquam imperdiet leo, in facilisis neque luctus ac. Duis semper aliquam luctus. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Maecenas tincidunt elit eu varius dictum. Vestibulum sapien est, viverra eu nisi eget, bibendum pharetra quam.";
const String texto2 = "Nullam consectetur augue eu ex consequat auctor. Curabitur in justo eu turpis cursus pellentesque luctus quis quam. Ut maximus leo massa, sed feugiat diam blandit et. Nam vulputate orci in porta accumsan. Vestibulum pretium facilisis magna, ut maximus felis vestibulum nec. Nulla pharetra sed lorem ut ultrices. Curabitur lacinia iaculis sodales. Mauris mattis est erat, sit amet vulputate nunc porttitor vel. Quisque nulla justo, rhoncus ut lectus quis, maximus hendrerit mi. Etiam tempus eleifend purus, id hendrerit ligula posuere ac. Etiam egestas felis vel mauris ultrices tristique in vitae nibh. Etiam eget justo purus. Aenean dapibus, augue eu ornare pellentesque, leo diam fringilla erat, pretium scelerisque purus nibh et ex. Suspendisse potenti. Etiam maximus commodo dapibus.";

class _MainAppState extends State<MainApp> {
  bool buttonEnabled = false;
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "48642578Q_Practica2Flutter",
      home: Scaffold(
        body: Padding(
            padding: const EdgeInsets.all(20),
            child: SingleChildScrollView(
              child: Column(
              children: [
                Image.asset(dirImg, width: 100, height: 100),
                //const Image(image: AssetImage(dirImg), width: 100, height: 100),
                //input text email and password
                TextField(decoration: const InputDecoration(hintText: "Email"), controller: emailController),
                const TextField(decoration: InputDecoration(hintText: "Password"), obscureText: true),
                const SizedBox(height: 16),
                Container( height: 200, width: 300,
                  child: const
                  Scrollbar(child: 
                    SingleChildScrollView(child:
                      Text(texto + texto2, textAlign: TextAlign.justify)
                    ),
                  )),
                const SizedBox(height: 16),
                //Button which changes his enable state with the value of buttonEnabled and throws a alert
                Container(
                  child: Row(
                    children: [
                      const Text("Estoy de acuerdo con los terminos: "),
                      Switch(value: buttonEnabled, onChanged: (value) => setState(() {
                        buttonEnabled = value;
                      })),
                  ],)
                ),

                ElevatedButton(onPressed: buttonEnabled ? () => showDialog(context: context, builder: (context) {
                  return AlertDialog(
                    title: const Text("Bienvenido"),
                    content: Text("Bienvendio ${emailController.text} a Flutter"),
                  );

                }) : null,
                child: const Text("Alerta")),
                //Switch whitch changes the value of buttonEnabled
              ],
              ),
            )
        ),
      ),
    );
  }
  
  @override
  State<StatefulWidget> createState() {
    // TODO: implement createState
    throw UnimplementedError();
  }
}
