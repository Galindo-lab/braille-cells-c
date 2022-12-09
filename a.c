
  puts("--- caracteres especiales ---");
  for(int i=' ';i < '/'+1; i++){
    printf("-[%c]-  %d\n",i, i - ' ' + SPACE);
    braile_character_print(charToBraile(i));
  }



  puts("--- Es numerico --- ");
  for(int i='0'-10;i < '9'+10; i++){
    if(is_numeric(i)){
      printf(" %c = %4d\n",i, i);
    }
  }


  puts("--- Es alfabetico --- ");
  for(int i='A';i < 'z'; i++){

    if(is_capital(i)) {
      printf(" %c = %4d | mayúscula\n",i,i);
      continue;
    }

    
    if(is_alphabetic(i)) {
      printf(" %c = %4d | minúscula\n",i,i);
      continue;
    }

  }
