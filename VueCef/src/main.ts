import 'vuetify/styles'
import './assets/globals.css'

import '@mdi/font/css/materialdesignicons.css'
import '@fontsource/roboto/index.css'

import { createApp } from 'vue'
import App from './App.vue'
import { createVuetify } from 'vuetify'
import { md2 } from 'vuetify/blueprints'

const vuetify = createVuetify({
    blueprint: md2,
    theme: {
        defaultTheme: 'dark',
    },
})

const app = createApp(App)

app.use(vuetify).mount('#app')
