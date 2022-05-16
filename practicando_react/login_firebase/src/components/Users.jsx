import React, { useEffect, useState } from 'react'
import {Link} from 'react-router-dom'
import axios from 'axios'


const Users = () => {
    const [users, setUsers] = useState([])
    
    const getUsers = async () => {
        const res = await axios.get('https://jsonplaceholder.typicode.com/users')
        const data = await res.data
        setUsers(data)
    } 

    useEffect(() => getUsers(), [])

    return (
        <div>
            <h2>Lista de Usuarios:</h2>
            <ul>
                {
                    users.map(user => 
                        <div key={user.name}>
                            <Link key={user.id} to={`/users/${user.id}`}>{user.name}</Link>
                        </div>
                    )
                }
            </ul>
        </div>
    )
}

export default Users