import React, { useState, useEffect } from 'react'
import { useParams } from 'react-router-dom'
import axios from 'axios'

const User = () => {
    const [user, setUser] = useState([])
    const {id} = useParams()

    useEffect(() => {
        const getUser = async () => {
        const res = await axios.get(`https://jsonplaceholder.typicode.com/users/${id}`)
        const user = await res.data
        setUser(user)
        }
        getUser()
    }, [id])

    return (
        <div>
            <h2>Usuario:</h2>
            <div>Nombre: {user.name}</div>
            <div>Email: {user.email}</div>
            <div>Teléfono: {user.phone}</div>
        </div>
    )
}

export default User