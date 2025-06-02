<script setup lang="ts">
import { ref } from 'vue'
const darkMode = ref(false)
</script>

<template>
  <v-app :theme="darkMode ? 'dark' : 'light'">
    <v-main>
      <v-container width="800">
        <v-card class="mb-3 py-2 px-3">
          <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed id vehicula justo, ac feugiat ligula. Aliquam erat volutpat. Nullam elementum felis maximus, lobortis magna a, viverra lorem. Vestibulum in leo placerat, ullamcorper velit auctor, faucibus felis. Morbi ultricies orci mi, sed dictum sem sagittis vel. Nullam tempor at lorem et tincidunt. Sed pellentesque luctus justo, eu pretium lacus efficitur dapibus. Mauris eu scelerisque tellus, in fermentum risus. Proin aliquet dui id lectus tempus tempus. Duis vestibulum varius ante, efficitur tincidunt neque iaculis sed. Donec dignissim nisi vitae suscipit venenatis.</p>
          <p>Aenean suscipit erat eu enim sollicitudin molestie. Sed vel velit non felis lobortis venenatis. Nunc interdum ligula purus, quis laoreet nunc sollicitudin ut. Ut vitae sem felis. Donec ut vestibulum sem. Curabitur rhoncus pulvinar euismod. Aliquam ut libero nec nisi iaculis rhoncus sit amet vel ante. Vivamus at dignissim massa. Sed posuere egestas eros nec sagittis.</p>
        </v-card>
        <v-card class="mb-3 py-2 px-3">
          <p>Nam molestie nisl aliquet eros semper tincidunt. Proin consequat eleifend risus, a viverra massa tempus eu. Donec pharetra mollis ipsum, et elementum dui lobortis ac. Aliquam finibus at metus vitae egestas. Vivamus iaculis gravida blandit. Nunc feugiat ex vel leo mattis feugiat. Nunc dapibus, nunc sodales hendrerit rhoncus, tortor tortor lacinia libero, quis aliquam turpis urna sit amet neque. Donec venenatis neque sit amet dolor blandit luctus. Pellentesque at eros sed ligula viverra lobortis id eu elit. Mauris ornare congue tempor. Fusce egestas mauris et dolor euismod, a auctor felis ultrices. Etiam nec eros nisl. Sed dictum arcu eget felis fermentum accumsan.</p>
        </v-card>
        <v-switch
          v-model="darkMode"
          label="Dark Mode"
        ></v-switch>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
</style>
