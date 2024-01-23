import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View, Switch, Image, Touchable, Button, ScrollView, TextInput } from 'react-native';
import React, { useState } from 'react';

export default function App() {

  const [isEnabled, setIsEnabled] = useState(false);
  const [correo, setCorreo] = useState('');

  const activarBtn = () => {
    if(isEnabled){
      setIsEnabled(false); 
    }else{
      setIsEnabled(true); 
    }
  }

  const bienv = () => {
    alert('Bienvenido ' + correo);
  }



  return (
    <View style={styles.container}>
      <Text style={{fontSize: 30, fontWeight: 'bold', paddingBottom: 10}}>Practica2_ReactNative</Text>
      <Image source={require('./assets/react.png')} style={{maxHeight: 150, maxWidth: 150}} />
      <View style={{paddingTop: 10, alignItems: 'flex-start'}}>
        <Text>Correo:</Text>
        <TextInput type="text" name="correo" id="correo" onChangeText={setCorreo} style={{ width: 300, height:50, padding: 8, borderRadius: 5, borderWidth: 1}}/>
        <Text>Contraseña:</Text>
        <TextInput type="password" name="contraseña" id="contraseña" style={{ width: 300, height:50, padding: 8, borderRadius: 5, borderWidth: 1}} />
      </View>
      <ScrollView style={{height: 200, width: 300, maxHeight: 200, maxWidth: 300, paddingTop: 10}}>
        <Text>Lorem ipsum dolor sit amet, consectetur adipiscing elit. In lacinia risus sed leo dapibus, a consequat elit mollis. Etiam mattis tellus rhoncus lorem pharetra, sit amet commodo erat convallis. Maecenas porta eget odio aliquam placerat. Morbi sem elit, placerat at dui in, vehicula ultricies felis. Aenean euismod ligula efficitur turpis pharetra vulputate. Nulla facilisi. Fusce bibendum turpis sapien, vitae gravida odio imperdiet tristique. Integer et elit egestas, luctus justo a, sagittis dolor. Integer eu porttitor magna, ut hendrerit leo. Cras commodo turpis a pharetra commodo. Duis aliquam imperdiet leo, in facilisis neque luctus ac. Duis semper aliquam luctus. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Maecenas tincidunt elit eu varius dictum. Vestibulum sapien est, viverra eu nisi eget, bibendum pharetra quam.

              Fusce gravida tristique nunc. Cras feugiat lorem quis hendrerit pretium. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Aliquam tristique arcu urna, a iaculis mi congue non. Aenean finibus arcu sed massa pellentesque sagittis. Morbi vestibulum non tellus quis condimentum. Duis ultrices lorem at pretium laoreet. Duis gravida ipsum eget arcu porttitor iaculis. Aenean ut orci eget nulla feugiat consectetur quis eget est. Nam vestibulum condimentum quam, id blandit diam vulputate ut. Proin vitae venenatis nisi.

              Vestibulum tempus feugiat velit, nec ullamcorper turpis ornare eu. Sed luctus leo eget dui luctus, non rutrum arcu molestie. Sed sodales nec metus non malesuada. Duis cursus imperdiet massa, id tristique nibh gravida id. Sed felis ex, dapibus vel tincidunt vel, tempus ac purus. Nullam feugiat mauris at magna congue, vel varius turpis venenatis. Sed scelerisque consequat convallis. Morbi nec neque non turpis maximus tristique ac id odio. Phasellus et sem dui.

              Fusce vestibulum lacinia elementum. Maecenas placerat ligula a tristique laoreet. Maecenas vehicula, dui quis tempor ullamcorper, nisi velit efficitur dolor, et sodales urna justo at sem. Maecenas sed vehicula tellus, quis malesuada justo. Praesent lacinia sem tempor ipsum gravida, ac interdum nulla accumsan. Duis at consequat ipsum, non maximus mi. In tellus est, laoreet id gravida non, pellentesque vitae erat. Nunc tempor dolor non velit laoreet semper. Mauris lacinia velit auctor, dictum nulla non, porttitor nisi. Donec vestibulum lectus elit, et bibendum quam euismod non. Aliquam erat volutpat.

              Etiam nibh neque, sagittis nec turpis id, tincidunt convallis tortor. In vitae massa vitae elit vestibulum sagittis. Nunc facilisis mi purus, sit amet viverra tortor dignissim vel. In ac dignissim tellus, nec elementum nunc. Integer sit amet erat ultrices, elementum ante sed, pulvinar felis. Integer massa erat, dapibus sed pretium nec, tempus vel quam. Pellentesque augue nibh, tempus vel orci at, sollicitudin fermentum turpis. Mauris et ligula non lectus eleifend fringilla. Ut tincidunt tellus ut dapibus auctor. Suspendisse id pulvinar est. Curabitur pulvinar quam et tellus scelerisque pharetra. Vestibulum augue tortor, laoreet quis finibus eget, bibendum in risus. Donec et orci nunc.
          </Text>
      </ScrollView>
      <View style={{flexDirection: 'row', alignItems: 'center'}}>
        <Text>Estoy de  acuerdo</Text>
        <Switch value={isEnabled}
          onValueChange={activarBtn}
        />
      </View>
      
      <Button title="Crear Cuenta" disabled={!isEnabled} onPress={bienv}/>
      <StatusBar style="auto" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
