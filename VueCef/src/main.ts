import 'vuetify/styles'
import './assets/globals.css'

import { createApp } from 'vue'
import App from './App.vue'
import { createVuetify } from 'vuetify'
import { md2 } from 'vuetify/blueprints'

const vuetify = createVuetify({
    blueprint: md2,
})

const app = createApp(App)

app.use(vuetify).mount('#app')
