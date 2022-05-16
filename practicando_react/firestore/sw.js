const CACHE_ELEMENTS =  []

const CACHE_NAME = 'app_cache'

self.addEventListener('install', (e) => {
    e.waitUntil(
        caches.open(CACHE_NAME)
        .then(cache => {cache.addAll()})
        .then(() => self.skipWaiting())
    )
})

self.addEventListener('activate', () => {
    const cacheWhiteList = [CACHE_NAME]
    e.waitUntil(
        caches.keys()
        .then(cachesNames => {
            return Promise.all(cachesNames.map(
                cache => cacheWhiteList.indexOf(cache) !== -1  ? cache : caches.delete(cache)
            ))
        })
        .catch(e => console.log(e))
        )
    self.clients.claim()
})

self.addEventListener('fetch', e => {
    e.respondWith(
        caches.match(e.request)
        .then(res => res ? res : fetch(e.request))
    )
})